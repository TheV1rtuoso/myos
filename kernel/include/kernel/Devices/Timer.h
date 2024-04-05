#pragma once

#include <kernel/types.h>


using ticks_t = u32;

class Timer
{
public:
    Timer() = default;
    Timer(Timer &&) = default;
    Timer(const Timer &) = default;
    Timer &operator=(Timer &&) = default;
    Timer &operator=(const Timer &) = default;
    ~Timer() = default;
    void tick();

private:
    ticks_t m_ticks = 0;
};
