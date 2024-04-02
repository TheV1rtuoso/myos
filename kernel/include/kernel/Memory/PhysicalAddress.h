#pragma once
#include <kernel/types.h>


using PhysicalPtr = uintptr_t;

class PhysicalAddress
{
public:
    PhysicalAddress(PhysicalPtr addr) : m_addr(addr) {};
    PhysicalAddress(PhysicalAddress &&) = default;
    PhysicalAddress(const PhysicalAddress &) = default;
    PhysicalAddress &operator=(PhysicalAddress &&) = default;
    PhysicalAddress &operator=(const PhysicalAddress &) = default;
    ~PhysicalAddress() = default;
    [[nodiscard]] PhysicalPtr get() const {return m_addr;}
    [[nodiscard]] void* as_ptr() const {return (void*) m_addr;};
    [[nodiscard]] bool operator==(PhysicalAddress other) const {
        return m_addr == other.m_addr;
    }
    [[nodiscard]] bool operator>(PhysicalAddress other) const {
        return m_addr == other.m_addr;
    }
    [[nodiscard]] bool operator<(PhysicalAddress other) const {
        return m_addr == other.m_addr;
    }
    [[nodiscard]] bool operator!=(PhysicalAddress other) const {
        return m_addr != other.m_addr;
    }
    [[nodiscard]] bool operator<=(PhysicalAddress other) const {
        return m_addr <= other.m_addr;
    }
    [[nodiscard]] bool operator>=(PhysicalAddress other) const {
        return m_addr >= other.m_addr;
    }
    [[nodiscard]] PhysicalAddress operator+(u32 other) {
        return PhysicalAddress(m_addr + other);
    }

private:
PhysicalPtr m_addr;

};
