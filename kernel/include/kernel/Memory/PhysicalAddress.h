
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

private:
PhysicalPtr m_addr;

};
