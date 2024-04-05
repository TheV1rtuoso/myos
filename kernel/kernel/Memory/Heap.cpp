#include <assert.h>
#include <kernel/Memory/Heap.h>
#include <kernel/types.h>

constexpr size_t MIN_SIZE = 8;
static u32 HEAP_INIT = 0;

static WatermarkAllocator wm_alloc{nullptr, 0};

WatermarkAllocator::WatermarkAllocator(uint8_t *start, size_t capacity)
    : m_watermark(start), m_capacity(capacity)
{
}

void *WatermarkAllocator::allocate(size_t size)
{
    if (m_capacity < size)
        return nullptr;
    m_capacity -= size;
    auto ret = m_watermark;
    m_watermark += size;
    return (void *)ret;
}
// Operator new[]
void *operator new(size_t size)
{
    assert(HEAP_INIT);
    if (size <= MIN_SIZE) {
        size = MIN_SIZE;
    }
    auto ptr = wm_alloc.allocate(size);
    //("allocate %d bytes: %p\n", (int) size, ptr);
    return ptr;
}
void *operator new[](size_t size)
{
    // You can simply forward this to operator new for simplicity
    return operator new(size);
}

// Operator delete[]
void operator delete[](void *p)
{
    // Forward to operator delete
    operator delete(p);
}

void operator delete[](void *p, size_t size)
{
    // Forward to operator delete
    (void)size;
    operator delete(p);
}

void operator delete(void *p)
{
    (void)p;
}
void operator delete(void *p, size_t size)
{
    (void)p;
    (void)size;
}



void heap_init(void *start, size_t size)
{
    (void)start;
    (void)size;
    auto ptr = static_cast<uint32_t *>(start);
    for (size_t i = 0; i < size / 4; ++i) {
        //printf("%x\n", (uint32_t)i);
        ptr[i] = 0x0;
    }
    for (size_t i = 0; i < size / 4; ++i) {
        assert(ptr[i] == 0x0);
    }
    wm_alloc = {(uint8_t *)start, size};
    HEAP_INIT = 1;
}
