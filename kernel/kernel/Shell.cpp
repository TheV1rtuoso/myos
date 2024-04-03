#include <assert.h>
#include <kernel/Devices/Keyboad.h>
#include <kernel/Devices/TTY.h>
#include <kernel/Shell.h>
#include <string.h>

char *Shell::prompt()
{
    auto buffer = new char[MAX_COMMAND_SIZE];
    size_t i = 0;
    while (1) {
        if (m_keyboard->is_ready()) {
            auto key = m_keyboard->read_keyboard_input();
            switch (key) {
            case 0:
                break;
            case '\n':
                CurrentTTY.newline();
                assert(i < MAX_COMMAND_SIZE);
                buffer[i] = '\0';
                return buffer;
            case '\b':
                if (i > 0) {
                    CurrentTTY.backspace();
                    i--;
                }
                break;
            default:
                if (i + 1 < MAX_COMMAND_SIZE) {
                    CurrentTTY.putchar(key);
                    buffer[i++] = key;
                }
            }
        }
    }
}

void Shell::run()
{
    while (1) {
        printf(">");
        char *buffer = prompt();
        if (strcmp(buffer, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        } else if (strncmp(buffer, "echo ", 5) == 0) {
            printf("%s\n", &buffer[5]);
        } else if (strcmp(buffer, "clear") == 0) {
            CurrentTTY.set_clear();
        } else {
            printf("Unknown command: %s\n", buffer);
        }
    }
}
