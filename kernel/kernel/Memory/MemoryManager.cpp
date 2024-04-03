#include <kernel/Memory/MemoryManager.h>
#include <kernel/Memory/PhysicalAddress.h>
#include <kernel/Memory/PhysicalAddressSpace.h>
#include <kernel/Memory/VirtualAddress.h>
#include <kernel/Memory/VirtualAddressSpace.h>
#include <stdio.h>

void MemoryManager::mmap(VirtualAddress vaddr,
                         PhysicalAddress phyaddr,
                         size_t n,
                         u16 flags)
{
    m_virt_space.mmap(vaddr, phyaddr, n, flags);
}

void *MemoryManager::get_pages(size_t n, int flags)
{
    auto phy_addr = m_phy_space.get_physical_pages(n);
    auto virt_addr = m_virt_space.get_virtual_addresses(n);

    mmap(virt_addr, phy_addr, n, flags);
    return virt_addr.as_ptr();
}
