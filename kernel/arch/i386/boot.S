#define ASM_FILE 1
#include <kernel/multiboot.h>


#define KERNEL_START 0xc0000000 #TODO remove duplication

# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

#define CR0_PE 0x00000001      /* Protection Enable. */
#define CR0_EM 0x00000004      /* (Floating-point) Emulation. */
#define CR0_PG 0x80000000      /* Paging. */
#define CR0_WP 0x00010000      /* Write-Protect enable in kernel mode. */

# Declare a header as in the Multiboot Standard.
.section .multiboot.header, "aw"
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.global boot_page_directory
# Reserve a stack for the initial thread.
.section .bss, "aw"
.align 4096
boot_page_directory:
	.skip 4096
boot_page_table1:
	.skip 4096
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.extern multiboot_info_ptr
.extern next_free_page
.type multiboot_info_ptr, @object
#.extern boot_page_directory

# The kernel entry point.
.section .multiboot.text, "a"
.code32

.global _start
.type _start, @function


_start:

	cmp $MULTIBOOT_BOOTLOADER_MAGIC, %eax # eax should contain the multiboot magicnumber
	jnz stop_cpu

test_a20:
	in $0x92, %al
	test %al, 2
	jnz multiboot_valid
	or $2, %al
	and %al, 0xFE
	out %al, $0x92

	multiboot_valid:
	mov $(multiboot_info_ptr- 0xC0000000), %edi
	mov %ebx, (%edi)
	cli

	# Physical address of boot_page_table1.
	# TODO: I recall seeing some assembly that used a macro to do the
	#       conversions to and from physical. Maybe this should be done in this
	#       code as well?
	movl $(boot_page_table1 - 0xC0000000), %edi
	# First address to map is address 0.
	# TODO: Start at the first kernel page instead. Alternatively map the first
	#       1 MiB as it can be generally useful, and there's no need to
	#       specially map the VGA buffer.
	movl $0, %esi
	# Map 1023 pages. The 1024th will be the VGA text buffer.
	movl $1023, %ecx

1:
	# Only map the kernel.
	#cmpl $_kernel_start, %esi
	#jl 2f
	cmpl $(_kernel_end - 0xC0000000), %esi
	jge 3f

	# TODO Map physical address as "present, writable". Note that this maps
	# .text and .rodata as writable. Mind security and map them as non-writable.
	movl %esi, %edx
	orl $0x003, %edx
	movl %edx, (%edi)

2:
	# Size of page is 4096 bytes.
	addl $4096, %esi
	# Size of entries in boot_page_table1 is 4 bytes.
	addl $4, %edi
	# Loop to the next entry if we haven't finished.
	loop 1b

3:
	mov $(next_free_page -0xc0000000), %edi
	add $0xc0000000, %esi
	mov %esi, (%edi)
	# Map VGA video memory to 0xC03FF000 as "present, writable".
	movl $(0x000B8000 | 0x003), boot_page_table1 - 0xC0000000 + 1023 * 4

	# The page table is used at both page directory entry 0 (virtually from 0x0
	# to 0x3FFFFF) (thus identity mapping the kernel) and page directory entry
	# 768 (virtually from 0xC0000000 to 0xC03FFFFF) (thus mapping it in the
	# higher half). The kernel is identity mapped because enabling paging does
	# not change the next instruction, which continues to be physical. The CPU
	# would instead page fault if there was no identity mapping.

	# Map the page table to both virtual addresses 0x00000000 and 0xC0000000.
	movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 0
	movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 768 * 4

	# Set cr3 to the address of the boot_page_directory.
	movl $(boot_page_directory - 0xC0000000), %ecx
	movl %ecx, %cr3

	# Enable paging and the write-protect bit.
	movl %cr0, %ecx
	orl $0x80010000, %ecx
	movl %ecx, %cr0

	# Jump to higher half with an absolute jump.
	lea 4f, %ecx
	jmp *%ecx



.section .text

.global stop_cpu
.global load_page_directory
.global enable_paging
.extern kernel_main

load_page_directory:
	push %ebp
	mov %esp, %ebp
	mov 8(%esp), %eax
	mov %eax, %cr3
	mov %ebp, %esp
	pop %ebp
	ret

enable_paging:
	push %ebp
	mov %esp, %ebp
	mov %cr0, %eax
	orl  $CR0_PG, %eax
	mov %eax, %cr0
	mov %ebp, %esp
	pop %ebp
	ret

4:
	movl $stack_top, %esp
	# Clear the identity mapped first page as its not needed
	#movl $0, boot_page_directory + 0


	lgdt gdtr

	#TODO: check if necessary,  add paging

reloadSegments:
	ljmp $0x08,$reload_CS # reload code segment by far jmp

reload_CS:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

stop_cpu:
	cli
	# Hang if kernel_main unexpectedly returns.
end_loop:	hlt
	jmp end_loop


### GDT
	.align 8
gdt_start:
	.quad 0x0000000000000000
	.quad 0x00CF9A000000FFFF
	.quad 0x00CF92000000FFFF
	.quad 0x00CFFA000000FFFF
	.quad 0x00CFF2000000FFFF
gdt_end:

	.align 8
gdtr:
	.word 0x27 #  For limit storage
    .long gdt_start # For base storage
