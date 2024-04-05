#pragma once
#include <assert.h>
#include <Singleton.h>

class Timer;
class PS_2Keyboard;
class TTY;
class MemoryManager;



class DeviceManager {

public:
    DeviceManager(Timer *timer, PS_2Keyboard *keyboard, TTY *tty)
        : m_timer(timer), m_keyboard(keyboard), m_tty(tty){};
    DeviceManager() = default;
    ~DeviceManager() = default;
    DeviceManager operator = (const DeviceManager &other) const
    {
        return DeviceManager(other.m_timer, other.m_keyboard, other.m_tty);
    }
    bool operator == (const DeviceManager &other) const
    {
        return m_timer == other.m_timer && m_keyboard == other.m_keyboard &&
               m_tty == other.m_tty;
    }

    void init_devices();

    void set_timer(Timer *timer)
    {
        m_timer = timer;
    }
    void set_keyboard(PS_2Keyboard *keyboard)
    {
        m_keyboard = keyboard;
    }
    void set_tty(TTY *tty)
    {
        m_tty = tty;
    }

    Timer *timer()
    {
        assert(m_timer != nullptr);
        return m_timer;
    }
    PS_2Keyboard *keyboard()
    {
        assert(m_keyboard != nullptr);
        return m_keyboard;
    }
    TTY *tty()
    {
        assert(m_tty != nullptr);
        return m_tty;
    }
    static DeviceManager& the();

private:
    Timer *m_timer = nullptr;
    PS_2Keyboard *m_keyboard = nullptr;
    TTY *m_tty = nullptr;
};
