#include <kernel/Devices/Keyboad.h>
#include <kernel/Devices/keymap.h>
#include <stdio.h>

using Keymap = PS2Key_DE;

bool PS_2Keyboard::is_ready() {
    return STATUS_READY_BIT & read_status();
}

u8 PS_2Keyboard::read_status()
{
    u8 status;
    __asm__ volatile("inb %1, %0" : "=a"(status) : "dN"(0x64));
    return status;
}

u8 PS_2Keyboard::read_keyboard_input()
{
    u8 data;
    __asm__ volatile("inb %1, %0" : "=a"(data) : "dN"(0x60));
    auto key = Keymap(data);
    printf("%x", data);
    return PS2KeyToASCII<Keymap>(key, false);
}
