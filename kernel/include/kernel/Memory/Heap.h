#pragma once
#include <stddef.h>
#include <stdint.h>

void *operator new(size_t size) noexcept;
void *operator new(size_t size) noexcept;


// Correspondingly, overwrite the global operator delete
void operator delete[](void *p) noexcept;
void operator delete(void *p) noexcept;
void operator delete(void *p, size_t size) noexcept;

void heap_init(void *start, size_t size);

class WatermarkAllocator {
public:
    WatermarkAllocator(uint8_t *start, size_t capacity);
    WatermarkAllocator(WatermarkAllocator &&) = default;
    WatermarkAllocator(const WatermarkAllocator &) = default;
    WatermarkAllocator &operator=(WatermarkAllocator &&) = default;
    WatermarkAllocator &operator=(const WatermarkAllocator &) = default;
    ~WatermarkAllocator() = default;

    void *allocate(size_t size);

private:
    uint8_t *m_watermark;
    size_t m_capacity;
};


class StubAllocator {
public:
    StubAllocator() = default;
    StubAllocator(StubAllocator &&) = default;
    StubAllocator(const StubAllocator &) = default;
    StubAllocator &operator=(StubAllocator &&) = default;
    StubAllocator &operator=(const StubAllocator &) = default;
    ~StubAllocator() = default;

private:
};
