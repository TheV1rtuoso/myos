#pragma once

#ifdef CONFIG_ARCH_I386
#include <kernel/arch/i386/vga.h>
#else
#error "Unsupported architecture"
#endif
