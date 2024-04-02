#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

void *memset(void *bufptr, int value, size_t size)
{
    assert(size % 4 == 0);
    auto ptr = static_cast<uint32_t *>(bufptr);
    for (size_t i = 0; i < size / 4; ++i) {
        ptr[i] = value;
    }
    return bufptr;
}
