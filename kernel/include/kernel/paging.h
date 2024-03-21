#pragma once

#include <stddef.h>
#include <stdint.h>

typedef uint32_t pte_t;
typedef uint32_t pde_t;
typedef uint32_t vaddr_t;

#define PDE_P (0x1 << 0)    // PDE Present
#define PDE_RW (0x1 << 1)   // PDE Read/Write
#define PDE_US (0x1 << 2)   // PDE USER/SUPERVISOR (S=0, U=1)
#define PDE_PWT (0x1 << 3)  // PDE Page-Level Write-through
#define PDE_PCD (0x1 << 4)  // PDE Cache Disable
#define PDE_A (0x1 << 5)    // PDE Accessed
#define PDE_D (0x1 << 6)    // PDE Dirty
#define PDE_PS (0x1 << 7)   // PDE Page-Size (0=4KB, 1=4MB?)
#define PDE_G (0x1 << 8)    // PDE Global
#define PDE_PAT (0x1 << 12) // PDE Page-Attribute-Table

#define PTE_P (0x1 << 0)   // PTE Present
#define PTE_RW (0x1 << 1)  // PTE Read/Write
#define PTE_US (0x1 << 2)  // PTE USER/SUPERVISOR (S=0, U=1)
#define PTE_PWT (0x1 << 3) // PTE Page-Level Write-through
#define PTE_PCD (0x1 << 4) // PTE Cache Disable
#define PTE_A (0x1 << 5)   // PTE Accessed
#define PTE_D (0x1 << 6)   // PTE Dirty
#define PTE_PAT                                                                \
    (0x1                                                                       \
     << 7) // PTE Page Attribute Table (Assuming 7 as the position, but you need to verify this based on your requirements)
#define PTE_G (0x1 << 8) // PTE Global


#ifdef __cplusplus
extern "C" {
#endif
void load_page_directory(pde_t *page_directory);
void enable_paging();
void fill_identity_page_table(pte_t *first_entry, vaddr_t from, size_t size);
void paging_init();

#ifdef __cplusplus
}
#endif
