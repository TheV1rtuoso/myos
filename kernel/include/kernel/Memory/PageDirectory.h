#include <kernel/Memory/PageTable.h>
#include <kernel/types.h>

constexpr u32 NUM_PDE = 1024;

constexpr u32 PDE_P = 0x1 << 0;    // PDE Present
constexpr u32 PDE_RW = 0x1 << 1;   // PDE Read/Write
constexpr u32 PDE_US = 0x1 << 2;   // PDE USER/SUPERVISOR (S=0, U=1)
constexpr u32 PDE_PWT = 0x1 << 3;  // PDE Page-Level Write-through
constexpr u32 PDE_PCD = 0x1 << 4;  // PDE Cache Disable
constexpr u32 PDE_A = 0x1 << 5;    // PDE Accessed
constexpr u32 PDE_D = 0x1 << 6;    // PDE Dirty
constexpr u32 PDE_PS = 0x1 << 7;   // PDE Page-Size (0=4KB, 1=4MB?)
constexpr u32 PDE_G = 0x1 << 8;    // PDE Global
constexpr u32 PDE_PAT = 0x1 << 12; // PDE Page-Attribute-Table

class PageDirectoryEntry {
public:

PageTable* page_table_addr() {
    return reinterpret_cast<PageTable*>(m_pde & 0xffe << 12);
}
bool check_flag(u16 flag) {
    //TODO check max flag value
    return flag & m_pde;
}
bool mask(u16 flag) {
    //TODO check max flag value
    m_pde = flag | m_pde;
}

bool set_flag(u16 flag) {
    //TODO check max flag value
    return flag | (m_pde & 0xfffff << 12);
}

private:
u32 m_pde;
};

class PageDirectory
{
public:
    PageDirectory() = default;
    PageDirectory(PageDirectory &&) = default;
    PageDirectory(const PageDirectory &) = default;
    PageDirectory &operator=(PageDirectory &&) = default;
    PageDirectory &operator=(const PageDirectory &) = default;
    ~PageDirectory() = default;

    PageDirectoryEntry& get(u32 idx) {
        return m_pd[idx];
    }


private:
    PageDirectoryEntry m_pd [NUM_PTE];
};
