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
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n == 0) {
        putchar('0');
        return 1;
    }
    char buf[32];
    int i = 0;
    do {
        buf[i++] = '0' + n % 10;
    } while ((n /= 10) > 0);
    print(buf, i);
    return i;
}

int32_t puts(const char *string)
{
    int32_t written = print(string, strlen(string));
    written += putchar('\n');
    return written;
}


int printf(const char *__restrict format, ...)
{
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0') {
        size_t maxrem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%')
                format++;
            size_t amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;
            if (maxrem < amount) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, amount))
                return -1;
            format += amount;
            written += amount;
            continue;
        }

        const char *format_begun_at = format++;

        if (*format == 'c') {
            format++;
            char c = (char)va_arg(parameters, int /*char promotes to int*/);
            if (!maxrem) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(&c, sizeof(c)))
                return -1;
            written++;
        } else if (*format == 's') {
            format++;
            const char *str = va_arg(parameters, const char *);
            size_t len = strlen(str);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(str, len))
                return -1;
            written += len;
        } else if (*format == 'd' || *format == 'i') {
            putchar('*');
            format++;
            int i = va_arg(parameters, int);
            written += print_decimal(i);
        } else {
            format = format_begun_at;
            size_t len = strlen(format);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, len))
                return -1;
            written += len;
            format += len;
        }
    }
    uint32_t len = strlen(format);
    print(format, len);
    return len;
}
