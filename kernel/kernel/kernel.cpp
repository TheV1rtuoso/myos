#include <assert.h>
#include <kernel/Devices/Keyboard.h>
#include <kernel/Devices/DeviceManager.h>
#include <kernel/Devices/tty.h>
#include <kernel/Memory/Heap.h>
#include <kernel/Memory/MemoryManager.h>
#include <kernel/Memory/MemoryRegion.h>
#include <kernel/Memory/PhysicalAddressSpace.h>
#include <kernel/Memory/VirtualAddress.h>
#include <kernel/Memory/VirtualAddressSpace.h>
#include <kernel/Shell.h>
#include <kernel/arch/i386/APIC.h>
#include <kernel/arch/i386/PIC.h>
#include <kernel/cpu.h>
#include <kernel/eflag.h>
#include <kernel/interrupts.h>
#include <kernel/io.h>
#include <kernel/multiboot.h>
#include <kernel/panic.h>
#include <stdio.h>
#include <string.h>
#include <kernel/Serial.h>

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

APIC *init_apic(MemoryManager &mem_mgr)
{
    if (!cpuid_apic()) {
        panic("CPU does not have APIC\n");
    }
    auto apic_mem = mem_mgr.map_physical_pages(PhysicalAddress(APIC_BASE),
                                               PTE_SU | PTE_P | PTE_RW,
                                               1);
    auto phy = mem_mgr.virt_space().translate_to_physical_addr(
        VirtualAddress(apic_mem));
    auto apic = new APIC(reinterpret_cast<uintptr_t>(apic_mem));
    APIC_EOI_RAII::set_instance(apic);
    apic->init();
    //printf("Set APIC Timer\n");
    return apic;
}

static TTY tty = TTY(VGA_WIDTH, VGA_HEIGHT, VGA_MEMORY);

extern "C" void kernel_main(void)
{
    DEBUG((char*)"Hello, kernel World, Welcome in tty1!\n");
    auto& dev_mgr = DeviceManager::the();
    tty = TTY(VGA_WIDTH, VGA_HEIGHT, VGA_MEMORY);
    tty.set_clear();
    dev_mgr.set_tty(&tty);
    idtr_init();
    disable_pic();
    disable_nmi();

    // init memory manager
    auto reg_ptr = get_usable_ram();
    MemoryRegion region = MemoryRegion(reg_ptr->addr, reg_ptr->len);
    auto vs = VirtualAddressSpace::from_cr3();
    auto phy_addr = PhysicalAddressSpace(region);
    auto mem_mgr = MemoryManager(phy_addr, vs);
    auto page_ptr = mem_mgr.get_pages(1024, PTE_P | PTE_RW);
    heap_init(page_ptr, 1024 * 4096);

    dev_mgr.init_devices();
    init_apic(mem_mgr);
    enable_interrupts();

    printf("Hello, kernel World, Welcome in tty1!\n");
    if (multiboot_info_ptr == nullptr) {
        panic("No multiboot header found\n");
    }
    //print_memory_map();
    Shell shell = Shell(dev_mgr.keyboard(), dev_mgr.tty());
    shell.run();
}
