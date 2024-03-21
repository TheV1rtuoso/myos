#define ASM_FILE 1
#include <kernel/multiboot.h>

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
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.extern multiboot_info_ptr
.type multiboot_info_ptr, @object
.global stop_cpu
.global _start
.global load_page_directory
.global enable_paging
.type _start, @function
# The kernel entry point.
.section .text
.code32

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


_start:

	cmp $MULTIBOOT_BOOTLOADER_MAGIC, %eax # eax should contain the multiboot magicnumber
	jz multiboot_valid
	jmp stop_cpu

	multiboot_valid:

	mov %ebx, multiboot_info_ptr
	movl $stack_top, %esp

	cli

	lgdt gdtr

	#TODO: check if necessary,  add paging

reloadSegments:
	ljmp $0x08,$reload_CS
		# The above might need adaptation based on the exact environment and context

reload_CS:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	# Call the global constructors.
	call _init
	call paging_init
	# Transfer control to the main kernel.
	call kernel_main

stop_cpu:
	cli
	# Hang if kernel_main unexpectedly returns.
1:	hlt
	jmp 1b
.size _start, . - _start


.globl reloadSegments

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
