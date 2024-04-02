#pragma once

#include <kernel/types.h>

class PageFaultError {

public:
    PageFaultError(u32 error_code) : m_error_code(error_code) {}
    [[nodiscard]] bool p() const noexcept
    {
        return bool(m_error_code & 1);
    }
    [[nodiscard]] bool w() const noexcept
    {
        return bool(m_error_code & (1 << 1));
    }
    [[nodiscard]] bool u() const noexcept
    {
        return bool(m_error_code & (1 << 2));
    }
    [[nodiscard]] bool r() const noexcept
    {
        return bool(m_error_code & (1 << 3));
    }
    [[nodiscard]] bool i() const noexcept
    {
        return bool(m_error_code & (1 << 4));
    }
    [[nodiscard]] bool pk() const noexcept
    {
        return bool(m_error_code & (1 << 5));
    }

    [[nodiscard]] bool ss() const noexcept
    {
        return bool(m_error_code & (1 << 6));
    }
    [[nodiscard]] bool sgx() const noexcept
    {
        return bool(m_error_code & (1 << 15));
    }

private:
    u32 m_error_code;
};

static_assert(sizeof(PageFaultError) == 4, "PageFaultError is not 32 bits");


extern "C" void page_fault_handler(PageFaultError error_code);
