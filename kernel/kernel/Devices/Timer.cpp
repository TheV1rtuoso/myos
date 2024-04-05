#include <kernel/Devices/Timer.h>
#include <kernel/Devices/tty.h>
#include <kernel/Devices/DeviceManager.h>
#include <stdio.h>

void display_clock(ticks_t ticks) {
        char buf[32];
        char tenth = (ticks % 100) / 10 + '0';
        char hundredth = (ticks % 100) % 10 + '0';
        snprintf(buf,
                 32,
                 "Time:%d.%c%c",
                 (unsigned)ticks / 100,
                 tenth,
                 hundredth);
        DeviceManager::the().tty()->write_footer(buf);
}


void Timer::tick() {
    m_ticks++;
    display_clock(m_ticks);
    return;
}
