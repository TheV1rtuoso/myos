#pragma once

typedef unsigned int uint32_t;
typedef int int32_t;

typedef unsigned char uint8_t;
typedef signed char int8_t;

typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned int uintptr_t;

#ifdef __cplusplus
static_assert(sizeof(unsigned int) == sizeof(int*), "Size of unsigned int is not equal to size of int pointer");
#endif
