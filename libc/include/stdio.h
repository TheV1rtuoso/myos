#ifndef _STDIO_H
#define _STDIO_H 1

#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif
uint32_t print_hex32(uint32_t n);
uint32_t print_hex64(uint64_t n);
int print_decimal(int n);
int printf(const char *__restrict, ...);
int putchar(int);
int puts(const char *);
int snprintf(char *str, size_t size, const char *format, ...);
#ifdef __cplusplus
}
#endif

#endif
