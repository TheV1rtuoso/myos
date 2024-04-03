#include <kernel/types.h>

constexpr u32 STATUS_READY_BIT = 1;

class PS_2Keyboard {
public:

    u8 read_keyboard_input();
    u8 read_status();
    bool is_ready();

private:
    bool m_is_shift_pressed = 0;
};
