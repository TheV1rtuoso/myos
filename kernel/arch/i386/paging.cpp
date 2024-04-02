#include <assert.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <stdio.h>
#include <string.h>

// TODO rewrite highlevel pagining functions
extern "C" uint32_t boot_page_directory[NUM_PDE];

uint32_t heap_page_table[NUM_PTE] __attribute__((aligned(PAGE_SIZE)));


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
        first_entry[i] = (from + (0x1 << PT_OFFSET_BITS) * i) |
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

constexpr uint32_t get_page_directory_entry_offset(uintptr_t vaddr)
{
    auto offset = static_cast<uint32_t>(vaddr >> PD_OFFSET_BITS);
    return offset;
}

constexpr bool is_start_of_pde(uintptr_t vaddr)
{
    auto offset = ~(1 << PD_OFFSET_BITS) - 1;
    return (vaddr & offset) == 0;
}

uintptr_t next_free_page;


void set_page_directory(uint32_t *pde, uint32_t *page_table, uint8_t flags)
{
    auto pt = (uintptr_t)page_table;
    *pde = pt | flags;
}

void *get_vaddr(uint32_t pd_off, uint32_t pt_off)
{
    return reinterpret_cast<void*>(pd_off << PD_OFFSET_BITS | pt_off << PT_OFFSET_BITS);
}

void clear_pages(void *start, int  n)
{
    auto int_ptr = (uint32_t*) start;
    for(int i = 0; i < n/4 ; ++i) {
        int_ptr[i] = 0;
        //printf("%x, %x\n",i, n/4 );
    }
    //memset(start, 0, n * PAGE_SIZE);
}


uint32_t flush_tlb() {
    uint32_t out;
    __asm__("mov %%cr3, %%ecx\n"
            "mov %%ecx, %%cr3\n":"=c"(out):);
    return out;
}


void *get_new_kernel_pages(size_t n)
{
    (void)n;
    auto pde = get_page_directory_entry_offset(next_free_page);
    if (!is_start_of_pde(next_free_page)) {
        pde++;
    }
    //auto cr3_pd = get_cr3();
    assert((pde == 768 + 1));
    printf("pde: %d\n", pde);
    uint32_t *phy_pt_addr = (uint32_t*) ((uintptr_t)heap_page_table - 0xc0000000);
    printf("phy addr: %p\n", phy_pt_addr);
    auto cr3_addr = get_cr3();
    printf("CR3: %p, BPD: %p\n", cr3_addr, boot_page_directory);
    //assert(cr3_addr == boot_page_directory);
    fill_kernel_page_table((uint32_t*) heap_page_table, 0x00400000, NUM_PTE);
    set_page_directory(&boot_page_directory[pde],
                       phy_pt_addr,
                       PTE_RW | PTE_P);
    auto ptr = (uint32_t*) 0xC0400000;
    auto phy_addr = get_phy_addr(cr3_addr, (vaddr_t) ptr);
    printf("Translated: %p", phy_addr);
    *ptr=0;
    //flush_tlb();
    //*ptr = 0;
    //clear_pages(ptr, n);
    return (void*) ptr;
}

void paging_init()
{
    printf("Initializing paging...\n");
    printf("Next free page: %x\n", (uintptr_t)next_free_page);
}
