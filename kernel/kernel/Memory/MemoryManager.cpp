#include <kernel/Memory/VirtualAddressSpace.h>
#include <kernel/Memory/PhysicalAddressSpace.h>
#include <kernel/Memory/PhysicalAddress.h>
#include <kernel/Memory/VirtualAddress.h>
#include <kernel/Memory/MemoryManager.h>

void MemoryManager::mmap(VirtualAddress vaddr, PhysicalAddress phyaddr) {
    m_virt_space.map(vaddr, phyaddr);
}

void *MemoryManager::get_pages(size_t n, int flags)
{
    auto phy_addr = m_phy_space.get_physical_pages(n);
    auto virt_addr = m_virt_space.get_virtual_addresses(n);
    mmap(virt_addr, phy_addr);
    return virt_addr.as_ptr();
}
