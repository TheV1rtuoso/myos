#include <kernel/panic.h>
#include <stdio.h>

void panic(const char *msg)
{
    puts(msg);
    stop_cpu();
}
