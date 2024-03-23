#include <kernel/panic.h>
#include <stdio.h>

void panic(const char *msg) {
    printf(msg);
    stop_cpu();
}
