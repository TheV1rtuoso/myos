#include <kernel/paging.h>


uint32_t page_directory[1024] __attribute__((aligned(4096)));


// identity pt of the first 4 MiB
uint32_t first_page_table[1024] __attribute__((aligned(4096)));


void fill_identity_page_table(uint32_t *first_entry, uint32_t from, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        first_entry[i] =
            ((0x1 << 12) * i) | (PTE_RW | PTE_P); // (from & 0x3FF000)+
    }
}

void clear_page_directory(void)
{
    for (int i = 0; i < 1024; i++) {
        // This sets the following flags to the pages:
        //   Supervisor: Only kernel-mode can access them
        //   Write Enabled: It can be both read from and written to
        //   Not Present: The page table is not present
        page_directory[i] = 0x00000002;
    }
}

void paging_init()
{
    clear_page_directory();
    fill_identity_page_table(first_page_table, 0, 4096);
    clear_page_directory();
    page_directory[0] = ((uint32_t)first_page_table) | PDE_RW | PDE_P;
    load_page_directory(page_directory);
    enable_paging();
}
