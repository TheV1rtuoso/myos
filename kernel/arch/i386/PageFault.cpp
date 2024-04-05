#include <kernel/Memory/PageFault.h>
#include <kernel/panic.h>
#include <stdio.h>

void page_fault_handler(PageFaultError error_code)
{
    uintptr_t vaddress;
    // virtual address of faulting page in cr2 register
    __asm__("mov %%cr2, %%eax" : "=r"(vaddress));
    printf("Error Code | Address: %x P: %x W: %x U: %x R: %x I: %x PK: %x SS: "
           "%x SGX: %x\n",
           vaddress,
           error_code.p(),
           error_code.w(),
           error_code.u(),
           error_code.r(),
           error_code.i(),
           error_code.pk(),
           error_code.ss(),
           error_code.sgx());
    if (!error_code.p()) {
        printf("Page fault on not present page");
    }
    stop_cpu();
}
