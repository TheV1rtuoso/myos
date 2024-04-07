#include <SinglyLinkedList.h>

class Thread;

class Processor {

public:

Thread *current_thread();
Thread* next_thread();
void run_thread(Thread* );
void add_thread(Thread *thread);

private:

Thread* m_running_thread;
SinglyLinkedList<Thread*> m_threads;
SinglyLinkedList<Thread*> m_blocked_threads;

};
