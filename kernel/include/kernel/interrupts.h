#pragma once

#include <kernel/types.h>

#define IDT_MAX_DESCRIPTORS 256


class InterruptFrame {
public:
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp_dummy;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;

    uint32_t vector_no;
    uint32_t error_code;
    void *frame_ptr;
    void *eip;
    uint16_t cs : 16;
    uint32_t eflags;
    uint32_t esp;
    uint16_t ss : 16;
};
static_assert(sizeof(InterruptFrame) == 64);

enum class InterruptVector : uint8_t {
    DivisionError = 0x0,
    Debug = 0x1,
    NonMaskableInterrupt = 0x2,
    Breakpoint = 0x3,
    Overflow = 0x4,
    BoundRangeExceeded = 0x5,
    InvalidOpcode = 0x6,
    DeviceNotAvailable = 0x7,
    DoubleFault = 0x8,
    CoprocessorSegmentOverrun = 0x9,
    InvalidTSS = 0xA,
    SegmentNotPresent = 0xB,
    StackSegmentFault = 0xC,
    GeneralProtectionFault = 0xD,
    PageFault = 0xE,
    // Reserved = 0xF
    x87FloatingPointException = 0x10,
    AlignmentCheck = 0x11,
    MachineCheck = 0x12,
    SIMDFloatingPointException = 0x13,
    VirtualizationException = 0x14,
    ControlProtectionException = 0x15,
    // Reserved values from 0x16 to 0x1B are skipped
    HypervisorInjectionException = 0x1C,
    VMMCommunicationException = 0x1D,
    SecurityException = 0x1E
    // Reserved = 0x1F
};

enum class InterruptType {
    Fault,
    Abort,
    Interrupt,
    Trap,
    Unknown
};

bool is_cpu_interrupt(uint8_t vector);
const char *interrupt_type_to_string(InterruptType type);

InterruptType get_interrupt_type(InterruptVector vec);
const char *get_interrupt_name(InterruptVector vec);

typedef void interrupt_handler_t(InterruptFrame *frame);



void idt_set_descriptor(uint8_t vector, void *isr, uint8_t flags);

typedef struct {
    uint16_t isr_low; // The lower 16 bits of the ISR's address
    uint16_t
        kernel_cs; // The GDT segment selector that the CPU will load into CS before calling the ISR
    uint8_t reserved;   // Set to zero
    uint8_t attributes; // Type and attributes; see the IDT page
    uint16_t isr_high;  // The higher 16 bits of the ISR's address
} __attribute__((aligned(8), packed)) idt_entry_t;
static_assert(sizeof(idt_entry_t) == 8, "idt_entry_t");

typedef struct {
    uint16_t limit;
    uintptr_t base;
} __attribute__((packed)) idtr_t;

void idtr_init(void);


extern "C" void exception_handler(
    InterruptFrame); // TODO check __attribute__((noreturn))

void enable_interrupts(void);
void disable_interrupts(void);
uint32_t interrupt_enabled(void);
