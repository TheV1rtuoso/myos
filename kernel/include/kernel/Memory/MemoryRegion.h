#include <kernel/types.h>

class MemoryRegion
{
public:
    MemoryRegion(u64 base, u64 length) : m_base(base), m_len(length) {};
    MemoryRegion(MemoryRegion &&) = default;
    MemoryRegion(const MemoryRegion &) = default;
    MemoryRegion &operator=(MemoryRegion &&) = default;
    MemoryRegion &operator=(const MemoryRegion &) = default;
    ~MemoryRegion() = default;

    u64 base_addr() const {return m_base;}
    u64 length() const {return m_base;}

private:
    u64 m_base;
    u64 m_len;
};
