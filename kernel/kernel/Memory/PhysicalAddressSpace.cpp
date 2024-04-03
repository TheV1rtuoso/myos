#include <kernel/Memory/MemoryRegion.h>
#include <kernel/Memory/PhysicalAddress.h>
#include <kernel/Memory/PhysicalAddressSpace.h>


PhysicalAddressSpace::PhysicalAddressSpace(MemoryRegion m_region)
    : m_region(m_region),
      m_allocator((uint8_t *)m_region.base_addr() + RESERVED_MEMORY,
                  m_region.length() - RESERVED_MEMORY)
{
}

PhysicalAddress PhysicalAddressSpace::get_physical_pages(size_t n)
{
    return PhysicalAddress((uintptr_t)m_allocator.allocate(n));
}
