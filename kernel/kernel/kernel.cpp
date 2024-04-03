#include <kernel/Devices/tty.h>
#include <kernel/Memory/Heap.h>
#include <kernel/Shell.h>
#include <kernel/cpu.h>
#include <kernel/interrupts.h>
#include <kernel/multiboot.h>

#include <assert.h>
#include <kernel/Devices/Keyboad.h>
#include <kernel/Memory/MemoryManager.h>
#include <kernel/Memory/MemoryRegion.h>
#include <kernel/Memory/PhysicalAddressSpace.h>
#include <kernel/Memory/VirtualAddressSpace.h>
#include <kernel/eflag.h>
#include <kernel/io.h>
#include <kernel/panic.h>
#include <stdio.h>
#include <string.h>

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

multiboot_memory_map_t *get_usable_ram()
{
    for (unsigned int i = 0; i < multiboot_info_ptr->mmap_length;
         i += sizeof(multiboot_memory_map_t)) {
        multiboot_memory_map_t *mmmt =
            (multiboot_memory_map_t *)(multiboot_info_ptr->mmap_addr + i);
        if (mmmt->type == 1)
            return mmmt;
    }
    return nullptr;
}

void init_apic()
{
    if (cpuid_apic()) {
        printf("CPU has APIC\n");
    } else {
        printf("CPU does not have APIC\n");
    }
    // TODO
}


extern "C" void kernel_main(void)
{
    CurrentTTY = TTY(VGA_WIDTH, VGA_HEIGHT, (VGAEntry *)0xC03FF000);
    CurrentTTY.set_clear();
    idtr_init();
    disable_nmi();
    init_apic();
    printf("Hello, kernel World!\n");
    if (multiboot_info_ptr == nullptr) {
        printf("No multiboot header found\n");
    }
    print_memory_map();

    // init memory manager
    auto reg_ptr = get_usable_ram();
    MemoryRegion region = MemoryRegion(reg_ptr->addr, reg_ptr->len);
    auto vs = VirtualAddressSpace::from_cr3();
    auto phy_addr = PhysicalAddressSpace(region);
    auto mem_mgr = MemoryManager(phy_addr, vs);
    auto page_ptr = mem_mgr.get_pages(1024, PTE_P | PTE_RW);
    heap_init(page_ptr, 1024 * 4096);
    auto keyboard = new PS_2Keyboard();

    Shell shell = Shell(keyboard, &CurrentTTY);
    shell.run();
}
