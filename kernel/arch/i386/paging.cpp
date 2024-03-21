#include <kernel/paging.h>

#define PAGE_SIZE 4096
#define NUM_PTE 1024
#define NUM_PDE 1024
#define PT_OFFSET_BITS 12

uint32_t page_directory[NUM_PDE] __attribute__((aligned(PAGE_SIZE)));


// identity pt of the first 4 MiB
uint32_t first_page_table[NUM_PTE] __attribute__((aligned(PAGE_SIZE)));


void fill_identity_page_table(uint32_t *first_entry, uint32_t from, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        first_entry[i] =
            ((from & 0x3FF000) + (0x1 << PT_OFFSET_BITS) * i) | (PTE_RW | PTE_P);
    }
}

void clear_page_directory(void)
{
    for (int i = 0; i < NUM_PDE ; i++) {
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
    fill_identity_page_table(first_page_table, 0, NUM_PTE);
    clear_page_directory();
    page_directory[0] = ((uintptr_t) first_page_table) | PDE_RW | PDE_P;
    load_page_directory(page_directory);
    enable_paging();
}
