#include <stdint.h>
#include <kernel/Memory/VirtualAddressSpace.h>
#include <kernel/Memory/VirtualAddress.h>
#include <kernel/Memory/PhysicalAddress.h>
#include <stdio.h>

extern PageTable reserved_page_table[64];
extern size_t reserved_page_table_idx;

VirtualAddress VirtualAddressSpace::get_virtual_addresses(size_t pages_n)
{
    auto vaddr = KernelVAddressSpaceAllocator.allocate(pages_n);
    return VirtualAddress(vaddr);
}

PageDirectory* get_cr3() {
    PageDirectory *out;
    __asm__("mov %%cr3, %0":"=r"(out):);
    return out;
}

uint32_t flush_tlb() {
    uint32_t out;
    __asm__("mov %%cr3, %%ecx\n"
            "mov %%ecx, %%cr3\n":"=c"(out):);
    return out;
}

//TODO error handling
PhysicalAddress VirtualAddressSpace::translate_to_physical_addr(VirtualAddress vaddr){
    auto pd_off = vaddr.get_page_directory_offset();
    auto pt_off = vaddr.get_page_table_offset();
    auto pde = m_page_directory->get(pd_off);
    if(!pde.check_flag(PDE_P)){
        printf("pde not present\n");
        return PhysicalAddress(0);
    }
    auto pt = pde.page_table_addr();
    auto pte = pt->get(pt_off);
    if(!pte.check_flag(PTE_P)){
        printf("pte not present\n");
        return PhysicalAddress(0);
    }
    return PhysicalAddress(pte.get() & 0xfffff000);
}


void VirtualAddressSpace::mmap(VirtualAddress vaddr, PhysicalAddress phyaddr, size_t n, u16 flags){

    auto pd_off = vaddr.get_page_directory_offset();
    auto pt_off = vaddr.get_page_table_offset();
    size_t allocated = 0;
    while (allocated < n)
    {
        auto pde = m_page_directory->get(pd_off);
        PageTable *pt;
        if(!pde.check_flag(PDE_P)){
            //printf("pt not present\n");
            pt = &reserved_page_table[reserved_page_table_idx++];
            //printf("Get PT VA:%p\n", pt);
            auto pt_addr = translate_to_physical_addr(VirtualAddress(pt));
            pt->clear();
            (*m_page_directory)[pd_off] = PageDirectoryEntry(pt_addr, flags | PDE_P);
        } else {
            pt = pde.page_table_addr();
        }

        allocated += pt->fill(pt_off, phyaddr, flags);
        pt_off = 0;
        pd_off++;
    }

}
