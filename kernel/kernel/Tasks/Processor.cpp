#include <kernel/Tasks/Processor.h>
#include <kernel/Tasks/Thread.h>


void Processor::add_thread(Thread* thread) {
    m_threads.push_back(thread);
}

Thread* Processor::current_thread() {
    return m_running_thread;
}


Thread* Processor::next_thread() {
    if (m_threads.empty()) {
       return &Thread::idle_thread;
    }
    auto t = m_threads.dequeue();
    if (m_running_thread == nullptr) {
        m_running_thread = m_threads.head();
    } else {
        m_running_thread = m_threads.next(m_running_thread);
    }

    return m_running_thread;
}
