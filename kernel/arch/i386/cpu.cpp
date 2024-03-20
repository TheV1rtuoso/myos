#include <kernel/cpu.h>
#include <stdint.h>

uint32_t cpuid_string(uint32_t code, uint32_t where[4])
{
    asm volatile("cpuid"
                 : "=a"(*where),
                   "=b"(*(where + 1)),
                   "=c"(*(where + 2)),
                   "=d"(*(where + 3))
                 : "a"(code));
    return (uint32_t)where[0];
}

uint32_t cpuid_apic()
{
    uint32_t where[4];
    asm volatile("cpuid"
                 : "=a"(*where),
                   "=b"(*(where + 1)),
                   "=c"(*(where + 2)),
                   "=d"(*(where + 3))
                 : "a"(0x1));
    return (int)(where[3] & 1 << 9);
}
