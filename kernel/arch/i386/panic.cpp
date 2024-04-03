#include <kernel/interrupts.h>
#include <kernel/panic.h>
#include <stdio.h>

void panic(const char *msg)
{
    disable_interrupts();
    puts(msg);
    stop_cpu();
}
