#include <kernel/cpu.h>
#include <kernel/interrupts.h>
#include <kernel/multiboot.h>
#include <kernel/tty.h>
#include <stdio.h>

multiboot_info_t *multiboot_info_ptr = nullptr;

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
        print_hex32(mmmt->type);
        putchar(' ');
        print_hex32(mmmt->size);
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
    terminal_initialize();
    idtr_init();
    printf("Hello, kernel World!\n");
    __asm__ volatile("int $0x3");
    if (cpuid_apic()) {
        printf("CPU has APIC\n");
    } else {
        printf("CPU does not have APIC\n");
    }

    if (multiboot_info_ptr == nullptr) {
        printf("No multiboot header found\n");
    }
    print_memory_map();
}
