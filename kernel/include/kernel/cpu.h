//#pragma once
#include <stdint.h>

uint32_t cpuid_string(uint32_t code, uint32_t where[4]);
uint32_t cpuid_apic(void);
