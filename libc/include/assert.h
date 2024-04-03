
#include <kernel/panic.h>
#include <stdio.h>

#define __assert(cond, file, line)                                             \
    printf("Assertion failed, %s %s:%d", cond, file, line);                    \
    stop_cpu();


#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else

#define assert(condition)                                                      \
    do {                                                                       \
        if (!(condition)) {                                                    \
            __assert(#condition, __FILE__, __LINE__);                          \
        }                                                                      \
    } while (0)
#endif
