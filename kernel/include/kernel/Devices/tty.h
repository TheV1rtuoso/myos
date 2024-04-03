#pragma once
#include <kernel/vga.h>
#include <span.h>
#include <stddef.h>


class TTY {
public:
    TTY(const size_t width, const size_t height, VGAEntry *vga_memory);
    TTY(TTY &&) = default;
    TTY(const TTY &) = default;
    TTY &operator=(TTY &&) = default;
    TTY &operator=(const TTY &) = default;
    ~TTY() = default;

    void fill(VGAEntry entry);
    void fill(uint8_t c);
    void putchar(int8_t c);
    void shift_screen_up(uint32_t delta);
    void newline(void);
    void write(const char *data, size_t size);
    void writestring(const char *data);
    bool backspace();
    void set_color(VGAColorEntry);
    void set_clear()
    {
        fill(' ');
        m_terminal_row = 0;
        m_terminal_column = 0;
    };
    void putentryat(VGAEntry entry, size_t x, size_t y);

private:
    size_t m_width;
    size_t m_height;
    libc::span<VGAEntry> m_console;
    size_t m_terminal_row = 0;
    size_t m_terminal_column = 0;
    VGAColorEntry m_terminal_color = VGAColorEntry(GREEN, BLACK);
};

extern TTY CurrentTTY;
