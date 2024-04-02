#include <stdint.h>
#include <kernel/paging.h>
#include <kernel/Memory/VirtualAddressSpace.h>
#include <kernel/Memory/VirtualAddress.h>
#include <kernel/Memory/PhysicalAddress.h>

void VirtualAddressSpace::mmap(VirtualAddress vaddr, PhysicalAddress phyaddr){
    auto pd_off = vaddr.get_page_directory_offset();
    m_page_directory[pd_off];
}
