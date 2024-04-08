#include <kernel/Tasks/Thread.h>


int idle_function () {
    while (1) {
        __asm__("hlt");
    }
}
void* create_stack(){
    auto ptr = new u8[STACK_SIZE];
    return ptr + STACK_SIZE;
}

Thread Thread::idle_thread = Thread(
    (Register) idle_function,
    (Register)0,
    (Register)0x2);


Thread *Thread::create(int(entry_point)(void))
{
    auto stack_ptr = create_stack();
    auto eflags = 0x2;
    return new Thread((Register)entry_point,
                      (Register)stack_ptr,
                      (Register)eflags);
}

Thread::Thread(Register eip, Register esp, Register eflags)
    : esp((Register)create_stack()), ebp(esp), eip((Register)eip),
      eflags(eflags)
{
}
