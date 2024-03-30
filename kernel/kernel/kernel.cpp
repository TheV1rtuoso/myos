#include <kernel/cpu.h>
#include <kernel/interrupts.h>
#include <kernel/multiboot.h>
#include <kernel/tty.h>
#include <stdio.h>

multiboot_info_t *multiboot_info_ptr = nullptr;
VGAEntry *VGA_MEMORY = (VGAEntry *)0xC03FF000; // remapped after boot

int print_memory_map()
{
    if (!(multiboot_info_ptr->flags >> 6 & 0x1)) {
        printf("invalid memory map given by GRUB bootloader");
        return -1;
    }

    for (unsigned int i = 0; i < multiboot_info_ptr->mmap_length;
         i += sizeof(multiboot_memory_map_t)) {
        multiboot_memory_map_t *mmmt =
            (multiboot_memory_map_t *)(multiboot_info_ptr->mmap_addr + i);

        printf("Start Addr | Length | Size | Type:");
        putchar(' ');
        print_hex64(mmmt->addr);
        putchar(' ');
        print_hex64(mmmt->len);
        putchar(' ');
        print_hex32(mmmt->size);
        putchar(' ');
        print_hex32(mmmt->type);
        putchar('\n');

        if (mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) {
            /*
             * Do something with this memory block!
             * BE WARNED that some of memory shown as availiable is actually
             * actively being used by the kernel! You'll need to take that
             * into account before writing to memory!
             */
        }
    }
    return 0;
}
extern "C" void kernel_main(void)
{

    CurrentTTY = TTY(VGA_WIDTH, VGA_HEIGHT, (VGAEntry *)0xC03FF000);
    CurrentTTY.set_clear();
    idtr_init();

    printf("Hello, kernel World!\n");
    if (cpuid_apic()) {
        printf("CPU has APIC\n");
    } else {
        printf("CPU does not have APIC\n");
    }

    if (multiboot_info_ptr == nullptr) {
        printf("No multiboot header found\n");
    }
    print_memory_map();

    enable_interrupts();
    __asm__ volatile("int $0x41");
    __asm__ volatile("int $0x42");
    __asm__ volatile("int $0x43");
    __asm__ volatile("int $0x44");
    __asm__ volatile("int $0x45");
    __asm__ volatile("int $0xe");
    printf("kernel_main finished\n");
    //uint8_t *unmapped_mem = (uint8_t *)0x30000000;
    //(*unmapped_mem)++;
}
