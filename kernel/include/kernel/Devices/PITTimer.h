#include <kernel/io.h>


constexpr u8 PIT_CHANNEL_0 = 0x40;
constexpr u8 PIT_CHANNEL_1 = 0x41;
constexpr u8 PIT_CHANNEL_2 = 0x42;
constexpr u8 PIT_COMMAND = 0x43;

constexpr int PIT_FREQUENCY = 1193182;

class PITTimer {
public:
    PITTimer();
    ~PITTimer();


    //ALWAYS_INLINE void start_timer();
    void prepare_sleep(int milliseconds) {
        auto counter = PIT_FREQUENCY / 1000 * milliseconds;
        outb(PIT_COMMAND, 0x34);
        outb(PIT_CHANNEL_0,counter & 0xFF);
        outb(PIT_CHANNEL_0,counter >> 8);
    }

private:

};
