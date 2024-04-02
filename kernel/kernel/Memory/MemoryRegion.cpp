#include <Memory>

class MemoryRegion
{
public:
    MemoryRegion() = default;
    MemoryRegion(MemoryRegion &&) = default;
    MemoryRegion(const MemoryRegion &) = default;
    MemoryRegion &operator=(MemoryRegion &&) = default;
    MemoryRegion &operator=(const MemoryRegion &) = default;
    ~MemoryRegion() = default;

private:
};
