#include <kernel/types.h>

constexpr u32 PAGE_SIZE = 4096;

constexpr u32 NUM_PTE = 1024;

constexpr u32 PTE_P = 0x1 << 0;    // PTE Present
constexpr u32 PTE_RW = 0x1 << 1;   // PTE Read/Write
constexpr u32 PTE_US = 0x1 << 2;   // PTE USER/SUPERVISOR (S=0, U=1)
constexpr u32 PTE_PWT = 0x1 << 3;  // PTE Page-Level Write-through
constexpr u32 PTE_PCD = 0x1 << 4;  // PTE Cache Disable
constexpr u32 PTE_A = 0x1 << 5;    // PTE Accessed
constexpr u32 PTE_D = 0x1 << 6;    // PTE Dirty
constexpr u32 PTE_PAT = 0x1 << 7; // TODO check
constexpr u32 PTE_G = 0x1 << 8;    // PTE Global

class PhysicalAddress;

class PageTableEntry
{
public:
    PageTableEntry(PhysicalAddress page_addr, u32 flags);
    PageTableEntry(PageTableEntry &&) = default;
    PageTableEntry(const PageTableEntry &) = default;
    PageTableEntry &operator=(PageTableEntry &&) = default;
    PageTableEntry &operator=(const PageTableEntry &) = default;
    ~PageTableEntry() = default;


private:
    u32 m_pte;
};

class PageTable
{
public:
    PageTable(PageTableEntry*);
    PageTable(PageTable &&) = default;
    PageTable(const PageTable &) = default;
  i  PageTable &operator=(PageTable &&) = default;
    PageTable &operator=(const PageTable &) = default;
    ~PageTable() = default;

private:
    PageTableEntry pt [NUM_PTE];
};
