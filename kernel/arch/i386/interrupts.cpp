#include <kernel/Devices/DeviceManager.h>
#include <kernel/Devices/Timer.h>
#include <kernel/Memory/PageFault.h>
#include <kernel/arch/i386/APIC.h>
#include <kernel/interrupts.h>
#include <kernel/io.h>
#include <kernel/panic.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define ERROR_STUB_NAME(x) (isr_err_stub##x)

static idt_entry_t idt[256];
static idtr_t idtr;
static uint32_t is_interrupt_enabled = 0;

extern "C" void *isr_stub_table;

void idt_set_descriptor(uint8_t vector, void *isr, uint8_t flags)
{
    uint32_t offset = (uintptr_t)isr;
    idt_entry_t *descriptor = &idt[vector];
    descriptor->isr_low = static_cast<uint16_t>(offset & 0xFFFF);
    descriptor->kernel_cs = 0x08; // kernel code segment
    descriptor->attributes = flags;
    descriptor->isr_high = static_cast<uint16_t>(offset >> 16);
    descriptor->reserved = 0;
}


void idtr_init(void)
{
    void **_isr_stub_table = &isr_stub_table;
    //(if (isr_stub_table != isr_stub_table_) panic("idtr_init!");
    idtr.base = (uintptr_t)&idt;
    idtr.limit = sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for (uint32_t i = 0; i < IDT_MAX_DESCRIPTORS; i++) {
        idt_set_descriptor(i, (void *)_isr_stub_table[i], 0x8E);
    }
    __asm__ volatile("lidt %0" : : "m"(idtr)); // load the new IDT
}

void disable_nmi()
{
    outb(0x70, inb(0x70) & 0x7F);
}


static size_t interrupt_counter = 0;
void exception_handler(InterruptFrame intr_frame)
{
    auto lock = InterrruptLock();
    interrupt_counter++;

    auto interrupt = static_cast<InterruptVector>(intr_frame.vector_no);
    /* TODO set to debug
    printf("CPU Interrupt %x, Reason: %s @rip: %p\n",
           intr_frame.vector_no,
           get_interrupt_name(interrupt),
           intr_frame.eip);*/

    if (get_interrupt_type(interrupt) == InterruptType::Abort) {
        printf("Abort, stoping CPU!\n");
        stop_cpu();
    }

    switch (interrupt) {
    case InterruptVector::PageFault: {
        page_fault_handler(PageFaultError(intr_frame.error_code));
        break;
    }
    case InterruptVector::TimerInterrupt: {
        APIC_EOI_RAII _eoi_raii;
        DeviceManager::the().timer()->tick();
        break;
    }
    default: {
        auto type = get_interrupt_type(interrupt);
        if (type == InterruptType::Fault || type == InterruptType::Abort) {
            // stop_cpu();
        }
    }
    }
}

void enable_interrupts(void)
{
    __asm__ volatile("sti");
    is_interrupt_enabled = 1; // TODO check if error occurs
}
void disable_interrupts(void)
{
    __asm__ volatile("cli");
    is_interrupt_enabled = 0; // TODO check if error occurs
}

bool interrupt_enabled(void)
{
    return is_interrupt_enabled;
}


bool is_cpu_interrupt(uint8_t vector)
{
    return vector < 0x20;
}


const char *interrupt_type_to_string(InterruptType type)
{
    switch (type) {
    case InterruptType::Fault:
        return "Fault";
    case InterruptType::Abort:
        return "Abort";
    case InterruptType::Interrupt:
        return "Interrupt";
    case InterruptType::Trap:
        return "Trap";
    default:
        return "Unknown";
    }
}

InterruptType get_interrupt_type(InterruptVector vec)
{
    switch (vec) {
    case InterruptVector::DivisionError:
    case InterruptVector::BoundRangeExceeded:
    case InterruptVector::InvalidOpcode:
    case InterruptVector::DeviceNotAvailable:
    case InterruptVector::CoprocessorSegmentOverrun:
    case InterruptVector::InvalidTSS:
    case InterruptVector::SegmentNotPresent:
    case InterruptVector::StackSegmentFault:
    case InterruptVector::GeneralProtectionFault:
    case InterruptVector::PageFault:
    case InterruptVector::x87FloatingPointException:
    case InterruptVector::AlignmentCheck:
    case InterruptVector::VirtualizationException:
    case InterruptVector::ControlProtectionException:
    case InterruptVector::HypervisorInjectionException:
    case InterruptVector::VMMCommunicationException:
    case InterruptVector::SecurityException:
        return InterruptType::Fault;

    case InterruptVector::DoubleFault:
    case InterruptVector::MachineCheck:
        return InterruptType::Abort;

    case InterruptVector::NonMaskableInterrupt:
        return InterruptType::Interrupt;

    case InterruptVector::Debug:
    case InterruptVector::Breakpoint:
    case InterruptVector::Overflow:
        return InterruptType::Trap;

    default:
        return InterruptType::Unknown;
    }
}


const char *get_interrupt_name(InterruptVector vec)
{
    switch (vec) {
    case InterruptVector::DivisionError:
        return "Division Error";
    case InterruptVector::Debug:
        return "Debug";
    case InterruptVector::NonMaskableInterrupt:
        return "Non-maskable Interrupt";
    case InterruptVector::Breakpoint:
        return "Breakpoint";
    case InterruptVector::Overflow:
        return "Overflow";
    case InterruptVector::BoundRangeExceeded:
        return "Bound Range Exceeded";
    case InterruptVector::InvalidOpcode:
        return "Invalid Opcode";
    case InterruptVector::DeviceNotAvailable:
        return "Device Not Available";
    case InterruptVector::DoubleFault:
        return "Double Fault";
    case InterruptVector::CoprocessorSegmentOverrun:
        return "Coprocessor Segment Overrun";
    case InterruptVector::InvalidTSS:
        return "Invalid TSS";
    case InterruptVector::SegmentNotPresent:
        return "Segment Not Present";
    case InterruptVector::StackSegmentFault:
        return "Stack-Segment Fault";
    case InterruptVector::GeneralProtectionFault:
        return "General Protection Fault";
    case InterruptVector::PageFault:
        return "Page Fault";
    case InterruptVector::x87FloatingPointException:
        return "x87 Floating-Point Exception";
    case InterruptVector::AlignmentCheck:
        return "Alignment Check";
    case InterruptVector::MachineCheck:
        return "Machine Check";
    case InterruptVector::SIMDFloatingPointException:
        return "SIMD Floating-Point Exception";
    case InterruptVector::VirtualizationException:
        return "Virtualization Exception";
    case InterruptVector::ControlProtectionException:
        return "Control Protection Exception";
    case InterruptVector::HypervisorInjectionException:
        return "Hypervisor Injection Exception";
    case InterruptVector::VMMCommunicationException:
        return "VMM Communication Exception";
    case InterruptVector::SecurityException:
        return "Security Exception";
    case InterruptVector::TimerInterrupt:
        return "Timer Interrupt";
    default:
        return "Unknown";
    }
}
