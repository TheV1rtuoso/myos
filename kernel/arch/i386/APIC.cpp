#include <kernel/arch/i386/APIC.h>
#include <kernel/Devices/PITTimer.h>

APIC *APIC_EOI_RAII::m_apic = nullptr;

void APIC::init()
{
    set_register(APIC_SPURIOUS_INTERRUPT_VECTOR_REGISTER, 0x1FF);
    //auto apic_id = register_value(APIC_LOCAL_ID_REGISTER) & (0xff << 24);
    //TODO debug printf("APIC ID: %x\n", apic_id);
    uint32_t time = calibrate_apic_timer((void*) m_base_ptr);
    //TODO check calc, add system bus freq calc
    uint32_t ticks = 0xFFFFFFFF - time;
    set_register(APIC_INITIAL_COUNT_REGISTER, ticks);
    set_register(APIC_DIVIDE_CONFIGURATION_REGISTER, 0x3);
    set_register(APIC_LVT_TIMER_REGISTER, TIMER_IRV | TIMER_PERIODIC);
}
