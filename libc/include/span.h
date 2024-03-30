#pragma once
#include <kernel/panic.h>
#include <stddef.h>

namespace libc {


template <typename T_>
class span {
    T_ *start; //TODO make unique
    size_t size;

public:
    span(T_ *start, size_t n) : start(start), size(n)
    {
        if (n == 0) {
            panic("Cannot create empty span");
        }
        if (start == nullptr) {
            panic("Cannot create nullptr span");
        }
    }
    span(span &) = default;
    span(const span &) = default;
    span(span &&) = default;
    //span(const span &&) = default;
    ~span() = default;

    span &operator=(const span &) = default;
    span &operator=(span &&) = default;


    [[nodiscard]] T_ &operator[](size_t n)
    {
        if (n >= size && n < 0) {
            panic("index out of range");
        }
        return start[n];
    }
    [[nodiscard]] const T_ &operator[](size_t n) const
    {
        if (n >= size && n < 0) {
            panic("index out of range");
        }
        return start[n];
    }
    [[nodiscard]] T_ &at(size_t n)
    {
        return start[n];
    }
    [[nodiscard]] const T_ &at(size_t n) const
    {
        return start[n];
    }

    [[nodiscard]] T_ *begin() const noexcept
    {
        return start;
    }
    [[nodiscard]] T_ *end() const noexcept
    {
        return &start[size];
    }
    [[nodiscard]] const T_ *cbegin() const noexcept
    {
        return start;
    }
    [[nodiscard]] const T_ *cend() const noexcept
    {
        return &start[size];
    }
    [[nodiscard]] size_t get_size() const noexcept
    {
        return size;
    }
};

} // namespace libc
