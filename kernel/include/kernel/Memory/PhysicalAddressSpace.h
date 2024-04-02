#include <kernel/types.h>

class MemoryRegion;

class PhysicalAddressSpace
{
public:
    PhysicalAddressSpace(const MemoryRegion&);
    PhysicalAddressSpace(PhysicalAddressSpace &&) = default;
    PhysicalAddressSpace(const PhysicalAddressSpace &) = default;
    PhysicalAddressSpace &operator=(PhysicalAddressSpace &&) = default;
    PhysicalAddressSpace &operator=(const PhysicalAddressSpace &) = default;
    ~PhysicalAddressSpace() = default;
    PhysicalAddress get_physical_pages(size_t n);

private:
    const MemoryRegion& m_region;

};
