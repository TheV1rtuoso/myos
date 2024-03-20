#pragma once

#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

typedef struct {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((aligned(8), packed)) idt_entry_t;


typedef struct {
	uint16_t	limit;
	uintptr_t	base;
} __attribute__((packed)) idtr_t;

void idtr_init(void);


extern "C" void exception_handler(void); // TODO check __attribute__((noreturn))

void enable_interrupts(void);
void disable_interrupts(void);
uint32_t interrupt_enabled(void);
