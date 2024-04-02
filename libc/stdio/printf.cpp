#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

bool print(const char *data, size_t length)
{
    const unsigned char *bytes = (const unsigned char *)data;
    for (size_t i = 0; i < length; i++)
        if (putchar(bytes[i]) == EOF)
            return false;
    return true;
}


#include <stdint.h> // For uint32_t and uint8_t types

uint32_t print_hex32(uint32_t n)
{
    uint32_t written_bytes =
        print("0x",
              2); // Assuming print function returns the number of bytes written

    if (n == 0) {
        return written_bytes + putchar('0'); // "0x" + "0"
    }

    uint32_t count = 0;  // Counter for the number of hex digits
    uint32_t mask = 0xF; // Mask for extracting the last 4 bits
    uint32_t shift =
        sizeof(uint32_t) * 8 - 4; // Start with the most significant hex digit

    // Find out where the first non-zero digit starts
    while (shift > 0 && !(n & (mask << shift))) {
        shift -= 4;
    }

    for (; shift < sizeof(uint32_t) * 8; shift -= 4) {
        uint8_t digit = (n >> shift) & mask;
        if (digit < 10)
            putchar('0' + digit);
        else
            putchar('a' + digit - 10);
        count++;
    }

    return written_bytes +
           count; // Include the bytes written by "0x" and the hex digits
}


uint32_t print_hex64(uint64_t n)
{
    uint32_t written_bytes =
        print("0x",
              2); // Assuming print function returns the number of bytes written

    if (n == 0) {
        return written_bytes + putchar('0'); // "0x" + "0"
    }

    uint32_t count = 0;  // Counter for the number of hex digits
    uint32_t mask = 0xF; // Mask for extracting the last 4 bits
    uint32_t shift =
        sizeof(uint32_t) * 8 - 4; // Start with the most significant hex digit

    // Find out where the first non-zero digit starts
    while (shift > 0 && !(n & (mask << shift))) {
        shift -= 4;
    }

    for (; shift < sizeof(uint64_t) * 8; shift -= 4) {
        uint8_t digit = (n >> shift) & mask;
        if (digit < 10)
            putchar('0' + digit);
        else
            putchar('a' + digit - 10);
        count++;
    }

    return written_bytes +
           count; // Include the bytes written by "0x" and the hex digits
}


int print_decimal(int n)
{
    if (n == 0) {
        putchar('0');
        return 1;
    }

    int count = 0;
    if (n == INT_MIN) {
        // Special case for INT_MIN
        print("-2147483648", 11);
        return 11; // Number of characters in "-2147483648"
    } else if (n < 0) {
        putchar('-');
        n = -n;
        count++;
    }

    char buf[32];
    int i = 0;
    while (n > 0) {
        buf[i++] = '0' + n % 10;
        n /= 10;
    }

    // Reverse the buffer before printing
    for (int j = i - 1; j >= 0; j--) {
        putchar(buf[j]);
    }

    return count + i; // Total printed characters
}

int32_t puts(const char *string)
{
    uint32_t len = strlen(string);
    if (!print(string, len))
        return -1;
    if (!putchar('\n'))
        return -1;
    return len + 1;
}


int printf(const char *__restrict format, ...)
{
    va_list parameters;
    va_start(parameters, format);
    int written = 0;

    while (*format != '\0') {
        size_t maxrem = INT_MAX - written; //TODO check

        if (*format != '%') {
            if (!putchar(*format))
                return -1;
            format++;
            continue;
        }
        const char *format_begun_at = format++;
        switch (*format) {
        case '%': {
            format++;
            putchar('%');
            written++;
            continue;
        }
        case 'c': {
            format++;
            char c = (char)va_arg(parameters, int);
            if (!putchar(c))
                return -1;
            written++;
            continue;
        }
        case 's': {
            format++;
            char *str = va_arg(parameters, char *);
            size_t len = strlen(str);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(str, len))
                return -1;
            written += len;
            break;
        }
        case 'x': {
            format++;
            uint32_t xint = va_arg(parameters, unsigned int);
            written += print_hex32(xint);
            break;
        }
        case 'p': {
            format++;
            void* ptr = va_arg(parameters, void*);
            written += print_hex32((uint32_t)ptr);
            break;
        }
        case 'd': {
            format++;
            uint32_t xint = va_arg(parameters, unsigned int);
            written += print_decimal(xint);
            break;
        }
        /*case 'i':
            assert(0);
        case 'u':
            assert(0);*/
        default: {
            if (!putchar('%'))
                return -1; // ignore and print formatter
            format = format_begun_at;
        }
        }
    }
    return written;
}
