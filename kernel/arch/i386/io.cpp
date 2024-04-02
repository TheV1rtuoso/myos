#include <kernel/io.h>

u8 inb(u16 port)
{
    u8 out;
    __asm__ volatile("inb %1, %0" : "=r"(out) : "Nd"(port));
    return out;
}

void outb(u16 port, u8 b)
{
    __asm__ volatile("outb %0, %1" ::"r"(b), "Nd"(port));
}
