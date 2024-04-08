#pragma once
#include <kernel/types.h>

template <typename T>
class SinglyLinkedList {
public:
    SinglyLinkedList();
    ~SinglyLinkedList();

    void push_back(T value){
        if(m_head == nullptr){
            m_head = new Node();
            m_head->data = value;
            m_last = m_head;
        } else {
            auto tmp = new Node();
            tmp->data = value;
            m_last->next = tmp;
            m_last = tmp;
        }
        m_size++;
    }
    T pop_back();

    void queue(T value) {
        if (m_head == nullptr) {
            m_head = new Node();
            m_head->data = value;
            m_last = m_head;
        } else {
            auto tmp = new Node();
            tmp->data = value;
            m_last->next = tmp;
            m_last = tmp;
        }
    }
T head() {
    if(size() == 0) return nullptr;
    return m_head->data;
};

    T dequeue() {
        if (m_head == nullptr) {
            return nullptr;
        }
        auto tmp = m_head;
        m_head = m_head->next;
        return tmp;
    };

    void remove(T value);

    bool contains(T value);
    size_t size() {return m_size;}
    bool empty() {return size() == 0;};
    size_t get(size_t index);
    void clear();

private:
    struct Node {
        T data;
        Node *next;
    };

    Node *m_head;
    Node *m_last;
    size_t m_size;
};
