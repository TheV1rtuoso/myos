#pragma once

#include <kernel/types.h>
#include <kernel/interrupts.h>
#include <assert.h>

extern "C" u32 calibrate_apic_timer(void* apic_base_ptr);

//constexpr uintptr_t APIC_BASE = 0xFFFC0000;
constexpr uintptr_t APIC_BASE = 0xFEE00000;
static constexpr uintptr_t APIC_LOCAL_ID_REGISTER = 0x20;
static constexpr uintptr_t APIC_VERSION_REGISTER = 0x30;
static constexpr uintptr_t APIC_TASK_PRIORITY_REGISTER = 0x80;
static constexpr uintptr_t APIC_ARBITRATION_PRIORITY_REGISTER = 0x90;
static constexpr uintptr_t APIC_PROCESSOR_PRIORITY_REGISTER = 0xA0;
static constexpr uintptr_t APIC_EOI_REGISTER = 0xB0;
static constexpr uintptr_t APIC_REMOTE_READ_REGISTER = 0xC0;
static constexpr uintptr_t APIC_LOGICAL_DESTINATION_REGISTER = 0xD0;
static constexpr uintptr_t APIC_DESTINATION_FORMAT_REGISTER = 0xE0;
static constexpr uintptr_t APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER = 0xF0;
static constexpr uintptr_t APIC_ISR0_REGISTER = 0x100;
static constexpr uintptr_t APIC_ISR1_REGISTER = 0x110;
static constexpr uintptr_t APIC_ISR2_REGISTER = 0x120;
static constexpr uintptr_t APIC_ISR3_REGISTER = 0x130;
static constexpr uintptr_t APIC_ISR4_REGISTER = 0x140;
static constexpr uintptr_t APIC_ISR5_REGISTER = 0x150;
static constexpr uintptr_t APIC_ISR6_REGISTER = 0x160;
static constexpr uintptr_t APIC_ISR7_REGISTER = 0x170;
static constexpr uintptr_t APIC_TMR0_REGISTER = 0x180;
static constexpr uintptr_t APIC_TMR1_REGISTER = 0x190;
static constexpr uintptr_t APIC_TMR2_REGISTER = 0x1A0;
static constexpr uintptr_t APIC_TMR3_REGISTER = 0x1B0;
static constexpr uintptr_t APIC_TMR4_REGISTER = 0x1C0;
static constexpr uintptr_t APIC_TMR5_REGISTER = 0x1D0;
static constexpr uintptr_t APIC_TMR6_REGISTER = 0x1E0;
static constexpr uintptr_t APIC_TMR7_REGISTER = 0x1F0;
static constexpr uintptr_t APIC_IRR0_REGISTER = 0x200;
static constexpr uintptr_t APIC_IRR1_REGISTER = 0x210;
static constexpr uintptr_t APIC_IRR2_REGISTER = 0x220;
static constexpr uintptr_t APIC_IRR3_REGISTER = 0x230;
static constexpr uintptr_t APIC_IRR4_REGISTER = 0x240;
static constexpr uintptr_t APIC_IRR5_REGISTER = 0x250;
static constexpr uintptr_t APIC_IRR6_REGISTER = 0x260;
static constexpr uintptr_t APIC_IRR7_REGISTER = 0x270;
static constexpr uintptr_t APIC_ERROR_STATUS_REGISTER = 0x280;
static constexpr uintptr_t APIC_LVT_CORRECTED_MACHINE_CHECK_INTERRUPT_REGISTER =
    0x2F0;
static constexpr uintptr_t APIC_INTERRUPT_COMMAND_REGISTER_LOW = 0x300;
static constexpr uintptr_t APIC_INTERRUPT_COMMAND_REGISTER_HIGH = 0x310;
static constexpr uintptr_t APIC_LVT_TIMER_REGISTER = 0x320;
static constexpr uintptr_t APIC_LVT_THERMAL_SENSOR_REGISTER = 0x330;
static constexpr uintptr_t APIC_LVT_PERFORMANCE_MONITORING_COUNTERS_REGISTER =
    0x340;
static constexpr uintptr_t APIC_LVT_LINT0_REGISTER = 0x350;
static constexpr uintptr_t APIC_LVT_LINT1_REGISTER = 0x360;
static constexpr uintptr_t APIC_LVT_ERROR_REGISTER = 0x370;
static constexpr uintptr_t APIC_INITIAL_COUNT_REGISTER = 0x380;
static constexpr uintptr_t APIC_CURRENT_COUNT_REGISTER = 0x390;
static constexpr uintptr_t APIC_DIVIDE_CONFIGURATION_REGISTER = 0x3E0;



using APICReg = uint32_t;

static constexpr APICReg TIMER_ONE_SHOT = 0x0;
static constexpr APICReg TIMER_PERIODIC = 0x1 << 17;
static constexpr APICReg TIMER_TSC_DEADLINE = 0x2 << 17;



class APIC {
public:
    APIC(uintptr_t base_ptr) : m_base_ptr(base_ptr)
    {}


    void init();

    constexpr APICReg* register_address(uintptr_t offset) const
    {
        assert(offset < 0x400);
        return reinterpret_cast<APICReg *>(m_base_ptr + offset);
    }

    void set_register(uintptr_t offset, APICReg value)
    {

        *register_address(offset) = value;
    }

    APICReg register_value(uintptr_t offset) const
    {
        return *register_address(offset);
    }

    template <uintptr_t offset, u8 size>
    void set_multi_register(APICReg* value)
    {
        for (u8 i = 0; i < size; i++) {
            auto reg = register_address(offset + i * 0x10);
            *reg = value[i];
        }
    }

    template <uintptr_t offset, u8 size>
    void get_multi_register(APICReg* buffer)
    {
        for (u8 i = 0; i < size; i++) {
            auto value = *register_address(offset + i * 0x10);
            buffer[i] = value;
        }
    }

    void get_isr(APICReg* buffer)
    {
        get_multi_register<APIC_ISR0_REGISTER, 8>(buffer);
    }
    void get_tmr(APICReg* buffer)
    {
        get_multi_register<APIC_TMR0_REGISTER, 8>(buffer);
    }
    void get_irr(APICReg* buffer)
    {
        get_multi_register<APIC_IRR0_REGISTER, 8>(buffer);
    }

    void set_isr(APICReg* buffer)
    {
        set_multi_register<APIC_ISR0_REGISTER, 8>(buffer);
    }
    void set_tmr(APICReg* buffer)
    {
        set_multi_register<APIC_TMR0_REGISTER, 8>(buffer);
    }
    void set_irr(APICReg* buffer)
    {
        set_multi_register<APIC_IRR0_REGISTER, 8>(buffer);
    }

    ~APIC() = default;
    APIC(const APIC &other) = default;
    APIC &operator=(const APIC &other) = default;
    APIC(APIC &&other) noexcept = default;
    APIC &operator=(APIC &&other) noexcept = default;

private:
    uintptr_t m_base_ptr;
};


class APIC_EOI_RAII{
public:
    APIC_EOI_RAII() = default;

    static void set_instance(APIC *apic)
    {
        m_apic = apic;
    }

    ~APIC_EOI_RAII()
    {
        m_apic->set_register(APIC_EOI_REGISTER, 0);
    }

private:
    static APIC *m_apic;
};
