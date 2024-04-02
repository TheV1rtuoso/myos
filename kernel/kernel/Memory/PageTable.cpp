#include <kernel/Memory/VirtualAddress.h>
#include <kernel/Memory/PageTable.h>
#include <kernel/Memory/PhysicalAddress.h>
#include <assert.h>


PageTable reserved_page_table[64] __attribute__((aligned(4096)));
size_t reserved_page_table_idx = 0;

void PageTable::clear() {
    for(auto &entry : m_entries) {
        entry = PageTableEntry();
    }
}

PageTableEntry::PageTableEntry(PhysicalAddress page_addr, u32 flags) : m_pte((page_addr.get() & 0xfffff000) | flags) {};

u16 PageTable::fill(u16 offset, PhysicalAddress phy_addr, u16 flags) {
    for (size_t i = offset; i < 1024; i++) {
        assert(phy_addr.get() % PAGE_SIZE == 0);
        m_entries[i] = PageTableEntry(phy_addr, flags);
        phy_addr = phy_addr + PAGE_SIZE;
    }
    return 1024 - offset;
}
