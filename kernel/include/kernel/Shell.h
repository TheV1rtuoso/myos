#pragma once
#include <kernel/types.h>

class PS_2Keyboard;
class TTY;

constexpr size_t MAX_COMMAND_SIZE = 256;

class Shell {
public:
    Shell(PS_2Keyboard *keyboard, TTY *tty)
        : m_keyboard(keyboard), m_tty(tty){};
    Shell(Shell &&) = default;
    Shell(const Shell &) = default;
    Shell &operator=(Shell &&) = default;
    Shell &operator=(const Shell &) = default;
    ~Shell() = default;
    void run();
    char *prompt();


private:
    PS_2Keyboard *m_keyboard;
    TTY *m_tty;
};
