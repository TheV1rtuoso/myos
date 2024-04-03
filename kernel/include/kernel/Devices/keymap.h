#pragma once

// Enum defining various PS/2 keyboard keys
enum class PS2Key : unsigned short {
    NONE = 0,
    ESC = 0x76,
    BACKSPACE = 0x66,
    TAB = 0x0D,
    ENTER = 0x5A,
    SPACE = 0x29,
    LSHIFT = 0x12,
    RSHIFT = 0x59,
    LCTRL = 0x14,
    LALT = 0x11,
    CAPS_LOCK = 0x58,

    // Alphanumeric keys
    A = 0x1C,
    B = 0x32,
    C = 0x21,
    D = 0x23,
    E = 0x24,
    F = 0x2B,
    G = 0x34,
    H = 0x33,
    I = 0x43,
    J = 0x3B,
    K = 0x42,
    L = 0x4B,
    M = 0x3A,
    N = 0x31,
    O = 0x44,
    P = 0x4D,
    Q = 0x15,
    R = 0x2D,
    S = 0x1B,
    T = 0x2C,
    U = 0x3C,
    V = 0x2A,
    W = 0x1D,
    X = 0x22,
    Y = 0x35,
    Z = 0x1A,

    // Number keys
    NUM_0 = 0x45,
    NUM_1 = 0x16,
    NUM_2 = 0x1E,
    NUM_3 = 0x26,
    NUM_4 = 0x25,
    NUM_5 = 0x2E,
    NUM_6 = 0x36,
    NUM_7 = 0x3D,
    NUM_8 = 0x3E,
    NUM_9 = 0x46,

    // Function keys
    F1 = 0x05,
    F2 = 0x06,
    F3 = 0x04,
    F4 = 0x0C,
    F5 = 0x03,
    F6 = 0x0B,
    F7 = 0x83,
    F8 = 0x0A,
    F9 = 0x01,
    F10 = 0x09,
    F11 = 0x78,
    F12 = 0x07,

    UP = 0xE075,
    DOWN = 0xE072,
    LEFT = 0xE06B,
    RIGHT = 0xE074,

    // Numeric keypad
    NUM_LOCK = 0x77,
    KEYPAD_DIVIDE = 0xE04A,
    KEYPAD_MULTIPLY = 0x7C,
    KEYPAD_MINUS = 0x7B,
    KEYPAD_PLUS = 0x79,
    KEYPAD_ENTER = 0xE05A,
    KEYPAD_1 = 0x69,
    KEYPAD_2 = 0x72,
    KEYPAD_3 = 0x7A,
    KEYPAD_4 = 0x6B,
    KEYPAD_5 = 0x73,
    KEYPAD_6 = 0x74,
    KEYPAD_7 = 0x6C,
    KEYPAD_8 = 0x75,
    KEYPAD_9 = 0x7D,
    KEYPAD_0 = 0x70,
    KEYPAD_DOT = 0x71,

    // Special keys
    //PRINT_SCREEN = 0xE012E07C,
    SCROLL_LOCK = 0x7E,
    //PAUSE = 0xE11477E1F014E077,
    INSERT = 0xE070,
    HOME = 0xE06C,
    PAGE_UP = 0xE07D,
    DELETE = 0xE071,
    END = 0xE069,
    PAGE_DOWN = 0xE07A,

    // Modifier keys
    RCTRL = 0xE014,
    RALT = 0xE011,
    LGUI = 0xE01F, // Windows key or Command key
    RGUI = 0xE027,
    APPS = 0xE02F, // Context menu key

    // Lock keys
    LLOCK = 0xE075, // Also used for arrow up
};

enum class PS2Key_DE : unsigned short {
    NONE = 0x00,
    ESC = 0x76,
    BACKSPACE = 0x66,
    TAB = 0x0D,
    ENTER = 0x5A,
    SPACE = 0x29,
    LSHIFT = 0x12,
    RSHIFT = 0x59,
    LCTRL = 0x14,
    LALT = 0x11,
    CAPS_LOCK = 0x58,

    // Letters
    A = 0x1C,
    B = 0x32,
    C = 0x21,
    D = 0x23,
    E = 0x24,
    F = 0x2B,
    G = 0x34,
    H = 0x33,
    I = 0x43,
    J = 0x3B,
    K = 0x42,
    L = 0x4B,
    M = 0x3A,
    N = 0x31,
    O = 0x44,
    P = 0x4D,
    Q = 0x15,
    R = 0x2D,
    S = 0x1B,
    T = 0x2C,
    U = 0x3C,
    V = 0x2A,
    W = 0x1D,
    X = 0x22,
    Y = 0x35,
    Z = 0x1A, // Note the swap of Y and Z

    // German-specific characters
    UMLAUT_A = 0x52, // Ä
    UMLAUT_O = 0x4C, // Ö
    UMLAUT_U = 0x3D, // Ü
    ESZETT = 0x4A,   // ß

    // Numbers
    NUM_1 = 0x16,
    NUM_2 = 0x1E,
    NUM_3 = 0x26,
    NUM_4 = 0x25,
    NUM_5 = 0x2E,
    NUM_6 = 0x36,
    NUM_7 = 0x3D,
    NUM_8 = 0x3E,
    NUM_9 = 0x46,
    NUM_0 = 0x45,

    // Function keys
    F1 = 0x05,
    F2 = 0x06,
    F3 = 0x04,
    F4 = 0x0C,
    F5 = 0x03,
    F6 = 0x0B,
    F7 = 0x83,
    F8 = 0x0A,
    F9 = 0x01,
    F10 = 0x09,
    F11 = 0x78,
    F12 = 0x07,

    // Special characters and punctuation
    MINUS = 0x4E,      // -
    EQUAL = 0x55,      // =
    LBRACKET = 0x54,   // Ü
    RBRACKET = 0x5B,   // +
    SEMICOLON = 0x4C,  // Ö
    APOSTROPHE = 0x52, // Ä
    GRAVE = 0x0E,      // ^
    BACKSLASH = 0x5D,  // #
    COMMA = 0x41,      // ,
    PERIOD = 0x49,     // .
    SLASH = 0x4A,      // -

    // Control keys TODO fix special keys
    //PRINT_SCREEN = 0xE012E07C, SCROLL_LOCK = 0x7E, PAUSE = 0xE11477E1F014E077,
    INSERT = 0xE070,
    HOME = 0xE06C,
    PAGE_UP = 0xE07D,
    DELETE = 0xE071,
    END = 0xE069,
    PAGE_DOWN = 0xE07A,

    // Arrow keys
    UP = 0xE075,
    DOWN = 0xE072,
    LEFT = 0xE06B,
    RIGHT = 0xE074,

    // Keypad
    NUM_LOCK = 0x77,
    KEYPAD_DIVIDE = 0xE04A,
    KEYPAD_MULTIPLY = 0x7C,
    KEYPAD_MINUS = 0x7B,
    KEYPAD_PLUS = 0x79,
    KEYPAD_ENTER = 0xE05A,
    KEYPAD_1 = 0x69,
    KEYPAD_2 = 0x72,
    KEYPAD_3 = 0x7A,
    KEYPAD_4 = 0x6B,
    KEYPAD_5 = 0x73,
    KEYPAD_6 = 0x74,
    KEYPAD_7 = 0x6C,
    KEYPAD_8 = 0x75,
    KEYPAD_9 = 0x7D,
    KEYPAD_0 = 0x70,
    KEYPAD_DOT = 0x71,

    // Modifier keys
    RCTRL = 0xE014,
    RALT = 0xE011, // RALT is often used as AltGr on German keyboards
    LGUI = 0xE01F,
    RGUI = 0xE027,
    APPS = 0xE02F,

    // Additional keys specific to the German layout might go here...
};


template <typename _PS2Key>
char PS2KeyToASCII(_PS2Key key, bool shiftPressed)
{
    switch (key) {
    // Letters
    case _PS2Key::A:
        return shiftPressed ? 'A' : 'a';
    case _PS2Key::B:
        return shiftPressed ? 'B' : 'b';
    case _PS2Key::C:
        return shiftPressed ? 'C' : 'c';
    case _PS2Key::D:
        return shiftPressed ? 'D' : 'd';
    case _PS2Key::E:
        return shiftPressed ? 'E' : 'e';
    case _PS2Key::F:
        return shiftPressed ? 'F' : 'f';
    case _PS2Key::G:
        return shiftPressed ? 'G' : 'g';
    case _PS2Key::H:
        return shiftPressed ? 'H' : 'h';
    case _PS2Key::I:
        return shiftPressed ? 'I' : 'i';
    case _PS2Key::J:
        return shiftPressed ? 'J' : 'j';
    case _PS2Key::K:
        return shiftPressed ? 'K' : 'k';
    case _PS2Key::L:
        return shiftPressed ? 'L' : 'l';
    case _PS2Key::M:
        return shiftPressed ? 'M' : 'm';
    case _PS2Key::N:
        return shiftPressed ? 'N' : 'n';
    case _PS2Key::O:
        return shiftPressed ? 'O' : 'o';
    case _PS2Key::P:
        return shiftPressed ? 'P' : 'p';
    case _PS2Key::Q:
        return shiftPressed ? 'Q' : 'q';
    case _PS2Key::R:
        return shiftPressed ? 'R' : 'r';
    case _PS2Key::S:
        return shiftPressed ? 'S' : 's';
    case _PS2Key::T:
        return shiftPressed ? 'T' : 't';
    case _PS2Key::U:
        return shiftPressed ? 'U' : 'u';
    case _PS2Key::V:
        return shiftPressed ? 'V' : 'v';
    case _PS2Key::W:
        return shiftPressed ? 'W' : 'w';
    case _PS2Key::X:
        return shiftPressed ? 'X' : 'x';
    case _PS2Key::Y:
        return shiftPressed ? 'Y' : 'y';
    case _PS2Key::Z:
        return shiftPressed ? 'Z' : 'z';

    // Numbers and their shifted symbols
    case _PS2Key::NUM_1:
        return shiftPressed ? '!' : '1';
    case _PS2Key::NUM_2:
        return shiftPressed ? '@' : '2';
    case _PS2Key::NUM_3:
        return shiftPressed ? '#' : '3';
    case _PS2Key::NUM_4:
        return shiftPressed ? '$' : '4';
    case _PS2Key::NUM_5:
        return shiftPressed ? '%' : '5';
    case _PS2Key::NUM_6:
        return shiftPressed ? '^' : '6';
    case _PS2Key::NUM_7:
        return shiftPressed ? '&' : '7';
    case _PS2Key::NUM_8:
        return shiftPressed ? '*' : '8';
    case _PS2Key::NUM_9:
        return shiftPressed ? '(' : '9';
    case _PS2Key::NUM_0:
        return shiftPressed ? ')' : '0';

    // Special characters and punctuation
    case _PS2Key::SPACE:
        return ' ';
    case _PS2Key::ENTER:
        return '\n';
    case _PS2Key::BACKSPACE:
        return '\b';
    case _PS2Key::TAB:
        return '\t';

    case _PS2Key::MINUS:
        return shiftPressed ? '_' : '-';
    case _PS2Key::EQUAL:
        return shiftPressed ? '+' : '=';
    case _PS2Key::LBRACKET:
        return shiftPressed ? '{' : '[';
    case _PS2Key::RBRACKET:
        return shiftPressed ? '}' : ']';
    case _PS2Key::BACKSLASH:
        return shiftPressed ? '|' : '\\';
    case _PS2Key::SEMICOLON:
        return shiftPressed ? ':' : ';';
    case _PS2Key::APOSTROPHE:
        return shiftPressed ? '"' : '\'';
    case _PS2Key::GRAVE:
        return shiftPressed ? '~' : '`';
    case _PS2Key::COMMA:
        return shiftPressed ? '<' : ',';
    case _PS2Key::PERIOD:
        return shiftPressed ? '>' : '.';
    case _PS2Key::SLASH:
        return shiftPressed ? '?' : '/';

        // Note: Additional special keys like function keys, control keys, etc., don't have a direct ASCII representation and are handled separately

    default:
        return 0; // No corresponding ASCII character or special key without ASCII representation
    }
}
