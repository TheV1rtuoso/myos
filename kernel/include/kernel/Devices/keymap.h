#pragma once
enum class PS2KeyKeyMap1 : unsigned short {
    NONE = 0x00,
    ESC_PRESSED = 0x01,
    NUM_1_PRESSED = 0x02,
    NUM_2_PRESSED = 0x03,
    NUM_3_PRESSED = 0x04,
    NUM_4_PRESSED = 0x05,
    NUM_5_PRESSED = 0x06,
    NUM_6_PRESSED = 0x07,
    NUM_7_PRESSED = 0x08,
    NUM_8_PRESSED = 0x09,
    NUM_9_PRESSED = 0x0A,
    NUM_0_PRESSED = 0x0B,
    MINUS_PRESSED = 0x0C,
    EQUAL_PRESSED = 0x0D,
    BACKSPACE_PRESSED = 0x0E,
    TAB_PRESSED = 0x0F,
    Q_PRESSED = 0x10,
    W_PRESSED = 0x11,
    E_PRESSED = 0x12,
    R_PRESSED = 0x13,
    T_PRESSED = 0x14,
    Y_PRESSED = 0x15,
    U_PRESSED = 0x16,
    I_PRESSED = 0x17,
    O_PRESSED = 0x18,
    P_PRESSED = 0x19,
    LBRACKET_PRESSED = 0x1A,
    RBRACKET_PRESSED = 0x1B,
    ENTER_PRESSED = 0x1C,
    LCTRL_PRESSED = 0x1D,
    A_PRESSED = 0x1E,
    S_PRESSED = 0x1F,
    D_PRESSED = 0x20,
    F_PRESSED = 0x21,
    G_PRESSED = 0x22,
    H_PRESSED = 0x23,
    J_PRESSED = 0x24,
    K_PRESSED = 0x25,
    L_PRESSED = 0x26,
    SEMICOLON_PRESSED = 0x27,
    APOSTROPHE_PRESSED = 0x28,
    GRAVE_PRESSED = 0x29,
    LSHIFT_PRESSED = 0x2A,
    BACKSLASH_PRESSED = 0x2B,
    Z_PRESSED = 0x2C,
    X_PRESSED = 0x2D,
    C_PRESSED = 0x2E,
    V_PRESSED = 0x2F,
    B_PRESSED = 0x30,
    N_PRESSED = 0x31,
    M_PRESSED = 0x32,
    COMMA_PRESSED = 0x33,
    PERIOD_PRESSED = 0x34,
    SLASH_PRESSED = 0x35,
    RSHIFT_PRESSED = 0x36,
    KEYPAD_MULTIPLY_PRESSED = 0x37,
    LALT_PRESSED = 0x38,
    SPACE_PRESSED = 0x39,
    CAPS_LOCK_PRESSED = 0x3A,
    F1_PRESSED = 0x3B,
    F2_PRESSED = 0x3C,
    F3_PRESSED = 0x3D,
    F4_PRESSED = 0x3E,
    F5_PRESSED = 0x3F,
    F6_PRESSED = 0x40,
    F7_PRESSED = 0x41,
    F8_PRESSED = 0x42,
    F9_PRESSED = 0x43,
    F10_PRESSED = 0x44,
    NUM_LOCK_PRESSED = 0x45,
    SCROLL_LOCK_PRESSED = 0x46,
    KEYPAD_7_PRESSED = 0x47,
    KEYPAD_8_PRESSED = 0x48,
    KEYPAD_9_PRESSED = 0x49,
    KEYPAD_MINUS_PRESSED = 0x4A,
    KEYPAD_4_PRESSED = 0x4B,
    KEYPAD_5_PRESSED = 0x4C,
    KEYPAD_6_PRESSED = 0x4D,
    KEYPAD_PLUS_PRESSED = 0x4E,
    KEYPAD_1_PRESSED = 0x4F,
    KEYPAD_2_PRESSED = 0x50,
    KEYPAD_3_PRESSED = 0x51,
    KEYPAD_0_PRESSED = 0x52,
    KEYPAD_DOT_PRESSED = 0x53,
    F11_PRESSED = 0x57,
    F12_PRESSED = 0x58,
    ESC_RELEASED = 0x81,
    NUM_1_RELEASED = 0x82,
    NUM_2_RELEASED = 0x83,
    NUM_3_RELEASED = 0x84,
    NUM_4_RELEASED = 0x85,
    NUM_5_RELEASED = 0x86,
    NUM_6_RELEASED = 0x87,
    NUM_7_RELEASED = 0x88,
    NUM_8_RELEASED = 0x89,
    NUM_9_RELEASED = 0x8A,
    NUM_0_RELEASED = 0x8B,
    MINUS_RELEASED = 0x8C,
    EQUAL_RELEASED = 0x8D,
    BACKSPACE_RELEASED = 0x8E,
    TAB_RELEASED = 0x8F,
    Q_RELEASED = 0x90,
    W_RELEASED = 0x91,
    E_RELEASED = 0x92,
    R_RELEASED = 0x93,
    T_RELEASED = 0x94,
    Y_RELEASED = 0x95,
    U_RELEASED = 0x96,
    I_RELEASED = 0x97,
    O_RELEASED = 0x98,
    P_RELEASED = 0x99,
    LBRACKET_RELEASED = 0x9A,
    RBRACKET_RELEASED = 0x9B,
    ENTER_RELEASED = 0x9C,
    LCTRL_RELEASED = 0x9D,
    A_RELEASED = 0x9E,
    S_RELEASED = 0x9F,
    D_RELEASED = 0xA0,
    F_RELEASED = 0xA1,
    G_RELEASED = 0xA2,
    H_RELEASED = 0xA3,
    J_RELEASED = 0xA4,
    K_RELEASED = 0xA5,
    L_RELEASED = 0xA6,
    SEMICOLON_RELEASED = 0xA7,
    APOSTROPHE_RELEASED = 0xA8,
    GRAVE_RELEASED = 0xA9,
    LSHIFT_RELEASED = 0xAA,
    BACKSLASH_RELEASED = 0xAB,
    Z_RELEASED = 0xAC,
    X_RELEASED = 0xAD,
    C_RELEASED = 0xAE

};

template <typename _PS2Key>
constexpr char PS2KeyToASCII(_PS2Key key, bool shiftPressed)
{
    switch (key) {
    // Letters
    case _PS2Key::A_PRESSED:
        return shiftPressed ? 'A' : 'a';
    case _PS2Key::B_PRESSED:
        return shiftPressed ? 'B' : 'b';
    case _PS2Key::C_PRESSED:
        return shiftPressed ? 'C' : 'c';
    case _PS2Key::D_PRESSED:
        return shiftPressed ? 'D' : 'd';
    case _PS2Key::E_PRESSED:
        return shiftPressed ? 'E' : 'e';
    case _PS2Key::F_PRESSED:
        return shiftPressed ? 'F' : 'f';
    case _PS2Key::G_PRESSED:
        return shiftPressed ? 'G' : 'g';
    case _PS2Key::H_PRESSED:
        return shiftPressed ? 'H' : 'h';
    case _PS2Key::I_PRESSED:
        return shiftPressed ? 'I' : 'i';
    case _PS2Key::J_PRESSED:
        return shiftPressed ? 'J' : 'j';
    case _PS2Key::K_PRESSED:
        return shiftPressed ? 'K' : 'k';
    case _PS2Key::L_PRESSED:
        return shiftPressed ? 'L' : 'l';
    case _PS2Key::M_PRESSED:
        return shiftPressed ? 'M' : 'm';
    case _PS2Key::N_PRESSED:
        return shiftPressed ? 'N' : 'n';
    case _PS2Key::O_PRESSED:
        return shiftPressed ? 'O' : 'o';
    case _PS2Key::P_PRESSED:
        return shiftPressed ? 'P' : 'p';
    case _PS2Key::Q_PRESSED:
        return shiftPressed ? 'Q' : 'q';
    case _PS2Key::R_PRESSED:
        return shiftPressed ? 'R' : 'r';
    case _PS2Key::S_PRESSED:
        return shiftPressed ? 'S' : 's';
    case _PS2Key::T_PRESSED:
        return shiftPressed ? 'T' : 't';
    case _PS2Key::U_PRESSED:
        return shiftPressed ? 'U' : 'u';
    case _PS2Key::V_PRESSED:
        return shiftPressed ? 'V' : 'v';
    case _PS2Key::W_PRESSED:
        return shiftPressed ? 'W' : 'w';
    case _PS2Key::X_PRESSED:
        return shiftPressed ? 'X' : 'x';
    case _PS2Key::Y_PRESSED:
        return shiftPressed ? 'Y' : 'y';
    case _PS2Key::Z_PRESSED:
        return shiftPressed ? 'Z' : 'z';

    // Numbers and their shifted symbols
    case _PS2Key::NUM_1_PRESSED:
        return shiftPressed ? '!' : '1';
    case _PS2Key::NUM_2_PRESSED:
        return shiftPressed ? '@' : '2';
    case _PS2Key::NUM_3_PRESSED:
        return shiftPressed ? '#' : '3';
    case _PS2Key::NUM_4_PRESSED:
        return shiftPressed ? '$' : '4';
    case _PS2Key::NUM_5_PRESSED:
        return shiftPressed ? '%' : '5';
    case _PS2Key::NUM_6_PRESSED:
        return shiftPressed ? '^' : '6';
    case _PS2Key::NUM_7_PRESSED:
        return shiftPressed ? '&' : '7';
    case _PS2Key::NUM_8_PRESSED:
        return shiftPressed ? '*' : '8';
    case _PS2Key::NUM_9_PRESSED:
        return shiftPressed ? '(' : '9';
    case _PS2Key::NUM_0_PRESSED:
        return shiftPressed ? ')' : '0';

    // Special characters and punctuation
    case _PS2Key::SPACE_PRESSED:
        return ' ';
    case _PS2Key::ENTER_PRESSED:
        return '\n';
    case _PS2Key::BACKSPACE_PRESSED:
        return '\b';
    case _PS2Key::TAB_PRESSED:
        return '\t';

    case _PS2Key::MINUS_PRESSED:
        return shiftPressed ? '_' : '-';
    case _PS2Key::SEMICOLON_PRESSED:
        return shiftPressed ? ':' : ';';
    case _PS2Key::RBRACKET_PRESSED:
        return shiftPressed ? '}' : ']';
    case _PS2Key::EQUAL_PRESSED:
        return shiftPressed ? '+' : '=';
    case _PS2Key::LBRACKET_PRESSED:
        return shiftPressed ? '{' : '[';
    case _PS2Key::BACKSLASH_PRESSED:
        return shiftPressed ? '|' : '\\';
    case _PS2Key::APOSTROPHE_PRESSED:
        return shiftPressed ? '"' : '\'';
    case _PS2Key::GRAVE_PRESSED:
        return shiftPressed ? '~' : '`';
    case _PS2Key::COMMA_PRESSED:
        return shiftPressed ? '<' : ',';
    case _PS2Key::PERIOD_PRESSED:
        return shiftPressed ? '>' : '.';
    case _PS2Key::SLASH_PRESSED:
        return shiftPressed ? '?' : '/';

    // Note: Additional special keys like function keys, control keys, etc., don't have a direct ASCII representation and are handled separately
    default:
        return 0; // No corresponding ASCII character or special key without ASCII representation
    }
}
