#include <kernel/eflag.h>

bool check_eflags(u32 mask)
{
    u32 eflags;
    __asm__("pushf\n"
            "pop %%eax"
            : "=a"(eflags)
            :);
    return eflags & mask;
}
