#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/Devices/tty.h>
#include <kernel/vga.h>
#include <span.h>

using namespace libc;


TTY CurrentTTY = TTY(VGA_WIDTH, VGA_HEIGHT, (VGAEntry *)0xC03FF000);

TTY::TTY(const size_t width, const size_t height, VGAEntry *vga_memory)
    : m_width(width), m_height(height), m_console(vga_memory, width * height)
{
}


void TTY::fill(VGAEntry entry)
{
    for (auto &console : m_console) {
        console = entry;
    }
}
void TTY::fill(uint8_t c)
{
    auto entry = VGAEntry(c, m_terminal_color);
    return TTY::fill(entry);
}

void TTY::putentryat(VGAEntry entry, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    m_console[index] = entry;
}

void TTY::shift_screen_up(uint32_t delta)
{
    if (delta > VGA_HEIGHT) {
        set_clear();
    }
    for (size_t y = delta; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = (y - delta) * VGA_WIDTH + x;
            m_console[index] = m_console[index + delta * VGA_WIDTH];
            m_console[index + delta * VGA_WIDTH] =
                VGAEntry(' ', m_terminal_color);
        }
    }
}


void TTY::newline(void)
{
    if (m_terminal_row + 1 == VGA_HEIGHT) {
        m_terminal_row = 0;
        //shift_screen_up(1);
    } else {
        m_terminal_row++;
    }
    m_terminal_column = 0;
}

void TTY::putchar(int8_t c)
{
    uint8_t uc = c;
    if (uc == '\n') {
        newline();
        return;
    }
    auto entry = VGAEntry(uc, m_terminal_color);
    putentryat(entry, m_terminal_column, m_terminal_row);
    if (++m_terminal_column == VGA_WIDTH) {
        newline();
    }
}

void TTY::write(const char *data, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        putchar(data[i]);
    }
}

void TTY::writestring(const char *data)
{
    write(data, strlen(data));
}

void TTY::set_color(VGAColorEntry color)
{
    m_terminal_color = color;
}

bool TTY::backspace()
{
    if (m_terminal_column == 0) {
        if (m_terminal_row != 0) {
            m_terminal_row--;
            m_terminal_column = VGA_WIDTH - 1;
        } else {
            return false;
        }
    } else {
        m_terminal_column--;
    }
    putentryat(VGAEntry(' ', m_terminal_color),
               m_terminal_column,
               m_terminal_row);
    return true;
}
