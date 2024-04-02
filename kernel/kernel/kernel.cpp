#include <kernel/cpu.h>
#include <kernel/interrupts.h>
#include <kernel/multiboot.h>
#include <kernel/paging.h>
#include <kernel/Heap.h>
#include <kernel/tty.h>

#include <kernel/Memory/MemoryManager.h>
#include <kernel/Memory/MemoryRegion.h>
#include <kernel/Memory/VirtualAddressSpace.h>
#include <kernel/Memory/PhysicalAddressSpace.h>

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

        reg = MemoryRegion(mmmt->addr, mmmt->size);
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

multiboot_memory_map_t* get_usable_ram() {
        for (unsigned int i = 0; i < multiboot_info_ptr->mmap_length;
         i += sizeof(multiboot_memory_map_t)) {
        multiboot_memory_map_t *mmmt =
            (multiboot_memory_map_t *)(multiboot_info_ptr->mmap_addr + i);
        if (mmmt->type == 1) return mmmt;
        }
        return nullptr;
}

void init_apic() {
    if (cpuid_apic()) {
        printf("CPU has APIC\n");
    } else {
        printf("CPU does not have APIC\n");
    }
    // TODO
}

extern "C" void kernel_main(void)
{
    print_memory_map();
    auto reg_ptr =get_usable_ram();
    MemoryRegion region = MemoryRegion(reg_ptr->addr, reg_ptr->len);
    auto vs = VirtualAddressSpace::from_cr3();
    auto phy_addr = PhysicalAddressSpace(region);
    MemoryManager mem_mgr {phy_addr, vs};
    auto page_ptr = mem_mgr.get_pages(1024);
    heap_init(page_ptr, 1024*4096);

    CurrentTTY = TTY(VGA_WIDTH, VGA_HEIGHT, (VGAEntry *)0xC03FF000);
    CurrentTTY.set_clear();
    idtr_init();
    enable_interrupts();
    paging_init();
    init_apic();
    printf("Hello, kernel World!\n");
    if (multiboot_info_ptr == nullptr) {
        printf("No multiboot header found\n");
    }
    print_memory_map();
    auto page = get_new_kernel_pages();
    printf("Got kernel page @%p\n", page);
    auto p = new int[64];
    auto p2 = new int[32];
    printf("Allocated array @%p\n", p);
    printf("Allocated array2 @%p\n", p2);
    printf("kernel_main end\n");
}
