#include <kernel/types.h>

template <typename T>
class Node;

template <typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void push_back(T value);
    void pop_back(T value);

    void queue(T value);
    void dequeue(T value);

    void remove(T value);

    bool contains(T value);
    size_t size() { return m_size; };
    size_t get(size_t index);

    Node<T>* begin() { return m_head; }
    Node<T>* end() { return nullptr; }


    void clear();

private:
    template <typename _T>
    struct Node {
        _T data;
        Node *next;
    };

    Node<T> *m_head;
    Node<T> *m_last;
    size_t m_size;
};
