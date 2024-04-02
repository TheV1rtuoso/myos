#pragma once

typedef unsigned int uint32_t;
typedef int int32_t;

typedef unsigned long long uint64_t;
typedef unsigned long long int64_t;

typedef unsigned char uint8_t;
typedef signed char int8_t;

typedef unsigned short uint16_t;
typedef short int16_t;

template<bool condition, class TrueType, class FalseType>
struct __Conditional {
    using Type = TrueType;
};
template<class TrueType, class FalseType>
struct __Conditional<false, TrueType, FalseType> {
    using Type = FalseType;
};

template<bool condition, class TrueType, class FalseType>
using Conditional = typename __Conditional<condition, TrueType, FalseType>::Type;

using uintptr_t = Conditional<sizeof(void*) == 4, uint32_t, uint64_t>;
/*
#ifdef __cplusplus
static_assert(sizeof(unsigned int) == sizeof(void *),
              "Size of unsigned int is not equal to size of int pointer");
static_assert(sizeof(unsigned long long) == 8, "Size of unsigned long");
#endif
*/
