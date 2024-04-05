#include <kernel/types.h>

enum KeyBoardCommand {
    SetLED = 0xED,
    Echo = 0xEE,
    SetScancodeSet = 0xF0,
    SetTypematicRate = 0xF3,
    Enable = 0xF4,
    Disable = 0xF5,
    SetDefault = 0xF6,
    Reset = 0xFF
};

class DeviceManager;
constexpr u32 STATUS_READY_BIT = 1;

class PS_2Keyboard {
    friend class DeviceManager;
public:
    u8 read_keyboard_input();
    u8 read_status();
    bool is_ready();
    ~PS_2Keyboard();

private:
    PS_2Keyboard() : m_is_shift_pressed(0) {};
    //std::vector <KeyBoardCommand> command_queue;
    bool m_is_shift_pressed = 0;
};
