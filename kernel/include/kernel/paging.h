#pragma once

#include <stddef.h>
#include <stdint.h>

typedef uint32_t pte_t;
typedef uint32_t pde_t;
typedef uint32_t vaddr_t;


void load_page_directory(pde_t *page_directory);
void enable_paging();
void fill_identity_page_table(pte_t *first_entry, vaddr_t from, size_t size);

void* get_new_kernel_pages(size_t n);
void paging_init();
uint32_t* get_cr3();
