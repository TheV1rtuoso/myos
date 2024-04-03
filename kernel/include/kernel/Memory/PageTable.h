#pragma once
#include <kernel/Memory/PhysicalAddress.h>
#include <kernel/types.h>
constexpr u32 PAGE_SIZE = 4096;

constexpr u32 NUM_PTE = 1024;

constexpr u32 PTE_P = 0x1 << 0;   // PTE Present
constexpr u32 PTE_RW = 0x1 << 1;  // PTE Read/Write
constexpr u32 PTE_US = 0x1 << 2;  // PTE USER/SUPERVISOR (S=0, U=1)
constexpr u32 PTE_PWT = 0x1 << 3; // PTE Page-Level Write-through
constexpr u32 PTE_PCD = 0x1 << 4; // PTE Cache Disable
constexpr u32 PTE_A = 0x1 << 5;   // PTE Accessed
constexpr u32 PTE_D = 0x1 << 6;   // PTE Dirty
constexpr u32 PTE_PAT = 0x1 << 7; // TODO check
constexpr u32 PTE_G = 0x1 << 8;   // PTE Global


class PageTableEntry {
public:
    PageTableEntry() : m_pte(0){};
    PageTableEntry(PhysicalAddress page_addr, u32 flags);
    PageTableEntry(PageTableEntry &&) = default;
    PageTableEntry(const PageTableEntry &) = default;
    PageTableEntry &operator=(PageTableEntry &&) = default;
    PageTableEntry &operator=(const PageTableEntry &) = default;
    ~PageTableEntry() = default;

    [[nodiscard]] u32 get() const
    {
        return m_pte;
    }
    [[nodiscard]] PhysicalAddress page_addr() const
    {
        return PhysicalAddress(m_pte & 0xfffff000);
    }

    bool check_flag(u16 flag)
    {
        //TODO check max flag value
        return flag & m_pte;
    }
    bool mask(u16 flag)
    {
        //TODO check max flag value
        m_pte = flag | m_pte;
    }

    bool set_flag(u16 flag)
    {
        //TODO check max flag value
        return flag | (m_pte & 0xfffff << 12);
    }

private:
    u32 m_pte;
};

class PageTable {
public:
    PageTable() = default;
    PageTable(PageTableEntry *);
    PageTable(PageTable &&) = default;
    PageTable(const PageTable &) = default;
    PageTable &operator=(PageTable &&) = default;
    PageTable &operator=(const PageTable &) = default;
    ~PageTable() = default;
    void clear();
    [[nodiscard]] PageTableEntry &get(u16 idx)
    {
        return m_entries[idx];
    }
    [[nodiscard]] PageTableEntry &operator[](u16 idx)
    {
        return m_entries[idx];
    }

    u16 fill(u16 offset, PhysicalAddress page_addr, u16 flags);

private:
    PageTableEntry m_entries[NUM_PTE];
};
