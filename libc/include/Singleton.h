//Based on Sererity OS Singleton.h

template <typename T>
struct SingletonInstanceCreator {
    static T* create() { return new T; }
};


//TODO Atomic

template <typename T, T* (*init_function)() = SingletonInstanceCreator<T>::create>
class Singleton {
public:
    Singleton() = default;
    static T* get(T*& instance) {
        if (instance == nullptr) {
            instance = init_function();
        }
        return instance;
    }

    T* ptr() {
        return get(m_instance);
    }

    T* operator->() const
    {
        return ptr();
    }
    operator T*() const { return ptr(); }
    operator T&() { return *ptr(); }
    operator *() const { return ptr(); }
    operator &() const { return *ptr(); }

private:
    mutable T* m_instance = nullptr;
    Singleton(const Singleton&) = delete; // Delete copy constructor
    Singleton& operator=(const Singleton&) = delete; // Delete assignment operator
};
