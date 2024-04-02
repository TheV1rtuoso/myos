#ifndef ARCH_I386_VGA_H
#define ARCH_I386_VGA_H

#include <stddef.h>
#include <stdint.h>

class VGAEntry;

constexpr size_t VGA_WIDTH{80};
constexpr size_t VGA_HEIGHT{25};


enum VGAColor : uint8_t {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15,
};

class VGAColorEntry {
public:
    VGAColorEntry(VGAColor fg, VGAColor bg) : m_fg(fg), m_bg(bg){};
    VGAColorEntry(VGAColorEntry &&) = default;
    VGAColorEntry(const VGAColorEntry &) = default;
    VGAColorEntry &operator=(VGAColorEntry &&) = default;
    VGAColorEntry &operator=(const VGAColorEntry &) = default;
    ~VGAColorEntry() = default;

private:
    uint8_t m_fg : 4;
    uint8_t m_bg : 4;
};

static_assert(sizeof(VGAColorEntry) == 1,
              "VGAColorEntry is not 1 byte in size");

class __attribute__((packed)) VGAEntry {
public:
    VGAEntry(uint8_t character, VGAColorEntry color)
        : m_character(character), m_color(color){};
    VGAEntry(VGAEntry &&) = default;
    VGAEntry(const VGAEntry &) = default;
    VGAEntry &operator=(VGAEntry &&) = default;
    VGAEntry &operator=(const VGAEntry &) = default;
    ~VGAEntry() = default;

private:
    uint8_t m_character;
    VGAColorEntry m_color;
};

static_assert(sizeof(VGAEntry) == 2, "VGAEntry is not 2 bytes");

#endif
