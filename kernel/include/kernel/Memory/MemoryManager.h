#pragma once
#include <kernel/types.h>

class PhysicalAddress;
class PhysicalAddressSpace;
class VirtualAddress;
class VirtualAddressSpace;

class MemoryManager {
public:
    MemoryManager(PhysicalAddressSpace& phy_space, VirtualAddressSpace& virt_space)
    : m_phy_space(phy_space), m_virt_space(virt_space) {};
    MemoryManager(MemoryManager &&) = default;
    MemoryManager(const MemoryManager &) = default;
    MemoryManager &operator=(MemoryManager &&) = default;
    MemoryManager &operator=(const MemoryManager &) = default;
    ~MemoryManager() = default;

    [[nodiscard]] void *get_pages(size_t n, int flags);
    void mmap(VirtualAddress vaddr, PhysicalAddress phyaddr, size_t n, u16 flags);

private:
    PhysicalAddressSpace& m_phy_space;
    VirtualAddressSpace& m_virt_space;
};
