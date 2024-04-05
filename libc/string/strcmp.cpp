#include <string.h>

int strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}
int strncmp(const char *str1, const char *str2, size_t n)
{
    while (n > 0 && *str1 && (*str1 == *str2)) {
        str1++;
        str2++;
        n--;
    }
    if (n == 0) {
        return 0;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

//TODO move

char *strcat(char *dest, const char *src)
{
    char *ptr = dest;

    // Move the pointer to the end of the destination string
    while (*ptr != '\0') {
        ptr++;
    }

    // Copy the source string to the end of the destination string
    while (*src != '\0') {
        *ptr++ = *src++;
    }

    // Add the null terminator to the concatenated string
    *ptr = '\0';

    return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    // Copy at most n characters from src to dest
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }

    // If src was shorter than n, pad dest with null characters
    for (; i < n; i++) {
        dest[i] = '\0';
    }

    return dest;
}
