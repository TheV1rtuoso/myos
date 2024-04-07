
#include <kernel/Memory/Heap.h>
#include <kernel/types.h>

using Register = u32;
constexpr u32 STACK_SIZE = 4096;


void* create_stack() {
    auto ptr = new u8[STACK_SIZE];
    return ptr + STACK_SIZE;
}

class Thread {

public:

static Thread idle_thread;
static Thread* create(int (entry_point)(void));


private:
Thread(Register eip, Register esp, Register eflags);
Register eax = 0;
Register ebx = 0;
Register ecx = 0;
Register edx = 0;
Register esi = 0;
Register edi = 0;
Register esp;
Register ebp;
Register eip;
Register eflags;
};
