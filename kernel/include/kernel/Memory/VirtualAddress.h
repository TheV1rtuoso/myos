#include <stdint.h>
#include <kernel/types.h>

constexpr u32 PT_OFFSET_BITS = 12;
constexpr u32 PD_OFFSET_BITS = 22;

class VirtualAddress {
public:
    VirtualAddress(void* vaddr) : m_vaddr((uintptr_t) vaddr) {}
    VirtualAddress(VirtualAddress &&) = default;
    VirtualAddress(const VirtualAddress &) = default;
    VirtualAddress &operator=(VirtualAddress &&) = default;
    VirtualAddress &operator=(const VirtualAddress &) = default;
    ~VirtualAddress() = default;

    [[nodiscard]] uintptr_t get() const {
        return m_vaddr;
    }
    [[nodiscard]] void* as_ptr() const {
        return (void*) m_vaddr;
    }

    uint16_t get_page_table_offset();
    uint16_t get_page_directory_offset();

private:
    uintptr_t m_vaddr;
};
