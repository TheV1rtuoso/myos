#include <kernel/types.h>
#include <kernel/Memory/Heap.h>
#include <kernel/Memory/MemoryRegion.h>

class MemoryRegion;
class PhysicalAddress;

constexpr u32 RESERVED_MEMORY = 0x4000000;

class PhysicalAddressSpace
{
public:
    PhysicalAddressSpace(MemoryRegion);
    PhysicalAddressSpace(PhysicalAddressSpace &&) = default;
    PhysicalAddressSpace(const PhysicalAddressSpace &) = default;
    PhysicalAddressSpace &operator=(PhysicalAddressSpace &&) = default;
    PhysicalAddressSpace &operator=(const PhysicalAddressSpace &) = default;
    ~PhysicalAddressSpace() = default;
    PhysicalAddress get_physical_pages(size_t n);

private:
    MemoryRegion m_region;
    WatermarkAllocator m_allocator;
};
