#include <kernel/paging.h>
#include <stdio.h>
#include <kernel/panic.h>

// TODO rewrite highlevel pagining functions

uint32_t boot_page_directory[NUM_PDE] __attribute__((aligned(PAGE_SIZE)));


// identity pt of the first 4 MiB
uint32_t first_page_table[NUM_PTE] __attribute__((aligned(PAGE_SIZE)));


void fill_identity_page_table(uint32_t *first_entry, uint32_t from, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        first_entry[i] = ((from & 0x3FF000) + (0x1 << PT_OFFSET_BITS) * i) |
                         (PTE_RW | PTE_P);
    }
}

void fill_kernel_page_table(uint32_t *first_entry, uint32_t from, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        first_entry[i] = ((from & 0x3FF000) + (0x1 << PT_OFFSET_BITS) * i) |
                         (PTE_RW | PTE_P);
    }
}

void clear_page_directory(void)
{
    for (int i = 0; i < NUM_PDE; i++) {
        // This sets the following flags to the pages:
        //   Supervisor: Only kernel-mode can access them
        //   Write Enabled: It can be both read from and written to
        //   Not Present: The page table is not present
        boot_page_directory[i] = 0x00000002;
    }
}

constexpr uint32_t *get_page_directory_entry(uintptr_t vaddr) {
    vaddr = vaddr >> PD_OFFSET_BITS;
    return &boot_page_directory[vaddr];
}

void paging_init()
{
    // identity map first 4 MiB
    fill_identity_page_table(first_page_table, 0, NUM_PTE);
    clear_page_directory();
    boot_page_directory[0] = ((uintptr_t)first_page_table) | PDE_RW | PDE_P;
    // map first kernel 4 MiB
    uint32_t *first_kernel_pde = get_page_directory_entry(KERNEL_START);

    if (first_kernel_pde != &boot_page_directory[768]) {
        panic("first_kernel_pde!= &boot_page_directory[0]\n");
    }

    first_kernel_pde[0] = ((uintptr_t)first_page_table) | PDE_RW | PDE_P;
    load_page_directory(boot_page_directory);
    enable_paging();
}
