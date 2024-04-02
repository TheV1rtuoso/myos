#include <stdio.h>

bool test_printf() {
    // Test 1: Simple String Test
    printf("Hello, World!\n");

    // Test 2: Character Test
    printf("Character: %c\n", 'A');

    // Test 3: String Variable Test
    printf("String: %s\n", "Test String");

    // Test 4: Hexadecimal Test
    printf("Hex: %x\n", 255);

    // Test 5: Multiple Format Specifiers
    printf("Char: %c, String: %s, Hex: %x\n", 'Z', "Hello", 127);

    // Test 6: Escaped Percent Sign Test
    printf("100%% Complete\n");

    // Test 7: No Format Specifiers
    printf("Just a test\n");

    // Test 8: Long String Test
    printf("%s\n", "This is a very long string that should still be printed correctly.");

    // Test 9: Boundary Test for Hexadecimal
    printf("Max unsigned int in hex: %x\n", UINT_MAX);

    // Test 10: Mixed Types
    printf("Char: %c, Hex: %x, String: %s\n", 'X', 48879, "Mixed");

    // Test with positive number
    printf("Positive: %d\n", 123);

    // Test with negative number
    printf("Negative: %d\n", -456);

    // Test with zero
    printf("Zero: %d\n", 0);

    // Test with INT_MAX
    printf("Max Int: %d\n", INT_MAX);

    // Test with INT_MIN
    printf("Min Int: %d\n", INT_MIN);

    return true;
}