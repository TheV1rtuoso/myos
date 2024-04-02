#include <kernel/types.h>
#include <kernel/Memory/PageDirectory.h>

class PhysicalAddress;
class VirtualAddress;
constexpr u32 KERNEL_START = 0xc0000000;


PageDirectory* get_cr3() {
    PageDirectory *out;
    __asm__("mov %%cr3, %%ecx":"=c"(out):);
    return out;
}


class VirtualAddressSpace {
public:
    VirtualAddressSpace(PageDirectory* page_directory) : m_page_directory(page_directory) {}
    VirtualAddressSpace(VirtualAddressSpace &&) = default;
    VirtualAddressSpace(const VirtualAddressSpace &) = default;
    VirtualAddressSpace &operator=(VirtualAddressSpace &&) = default;
    VirtualAddressSpace &operator=(const VirtualAddressSpace &) = default;
    ~VirtualAddressSpace() = default;

    static VirtualAddressSpace from_cr3() {
        return VirtualAddressSpace(get_cr3());
    }

    PhysicalAddress translate_to_physical_addr(VirtualAddress vaddr);
    VirtualAddress get_virtual_addresses(size_t pages_n);
    void mmap(VirtualAddress vaddr, PhysicalAddress phyaddr);

private:
PageDirectory* m_page_directory;
};
