
#include <kernel/interrupts.h>
#include <stdint.h>
#include <stdio.h>

static idt_entry_t idt[256];
static idtr_t idtr;
extern void* isr_stub_table [];
static uint32_t is_interrupt_enabled = 0;

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; // kernel code segment
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    descriptor->reserved       = 0;
}

void idtr_init(void) {
    idtr.base = (uintptr_t) &idt;
    idtr.limit = sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for (uint32_t i = 0; i < 32; i++) {
        idt_set_descriptor(i, &isr_stub_table[i], 0x8E);
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag

}


void exception_handler() {
    printf("Hello from  exception handler!\n");
    //__asm__ volatile ("cli; hlt"); // Completely hangs the computer
}

void enable_interrupts(void) {
    __asm__ volatile ("sti");
    is_interrupt_enabled = 1; // TODO check if error occurs
}
void disable_interrupts(void){
    __asm__ volatile ("cli");
    is_interrupt_enabled = 0; // TODO check if error occurs
}

uint32_t interrupt_enabled(void){
    return is_interrupt_enabled;
}
