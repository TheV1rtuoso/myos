#include <kernel/Memory/PageFault.h>
#include <kernel/panic.h>
#include <stdio.h>

void page_fault_handler(PageFaultError error_code)
{
    uintptr_t vaddress;
    // virtual address of faulting page in cr2 register
    __asm__("mov %%cr2, %%eax" : "=r"(vaddress));
    if (error_code.p()) { // TODO
        panic("Page fault on present page not handled");
    }
    print_hex32(vaddress);
    printf("Page fault on not present page");
}
