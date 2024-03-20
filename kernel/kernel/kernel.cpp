#include <stdio.h>

#include <kernel/cpu.h>
#include <kernel/interrupts.h>
#include <kernel/tty.h>

extern "C" void kernel_main(void)
{
    terminal_initialize();
    idtr_init();
    printf("Hello, kernel World!\n");
    __asm__ volatile("int $0x3");
    if (cpuid_apic()) {
        printf("CPU has APIC\n");
    } else {
        printf("CPU does not have APIC\n");
    }
}
