

extern "C" {
void stop_cpu(void) __attribute__((noreturn));
}

void panic(const char *msg) __attribute__((noreturn));
