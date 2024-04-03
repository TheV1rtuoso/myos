#pragma once
#include <kernel/Memory/Heap.h>
#include <kernel/Memory/PageDirectory.h>
#include <kernel/types.h>

class PhysicalAddress;
class VirtualAddress;
constexpr u32 KERNEL_START = 0xc0000000;


PageDirectory *get_cr3();

//FIXME: get_actual free start
static u8 *KERNEL_FREE_START = reinterpret_cast<u8 *>(0xc0400000);
constexpr size_t MAX_VADDR = 0xffffffff;


class VirtualAddressSpace {
public:
    VirtualAddressSpace(PageDirectory *page_directory)
        : m_page_directory(page_directory)
    {
    }
    VirtualAddressSpace(VirtualAddressSpace &&) = default;
    VirtualAddressSpace(const VirtualAddressSpace &) = default;
    VirtualAddressSpace &operator=(VirtualAddressSpace &&) = default;
    VirtualAddressSpace &operator=(const VirtualAddressSpace &) = default;
    ~VirtualAddressSpace() = default;

    static VirtualAddressSpace from_cr3()
    {
        return VirtualAddressSpace(get_cr3());
    }

    PhysicalAddress translate_to_physical_addr(VirtualAddress vaddr);
    VirtualAddress get_virtual_addresses(size_t pages_n);
    void mmap(VirtualAddress vaddr,
              PhysicalAddress phyaddr,
              size_t n,
              u16 flags);

private:
    PageDirectory *m_page_directory;
    WatermarkAllocator KernelVAddressSpaceAllocator{KERNEL_FREE_START,
                                                    MAX_VADDR};
};
