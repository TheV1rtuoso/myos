
template <class T>
class SmartPtr{
    SmartPtr(T* ptr) : m_ptr(ptr) {}

    T& operator* () const {
        return *m_ptr;
    }

    T* operator->() const {
        return m_ptr;
    }

    T* ptr() {
        return m_ptr;
    }

private:
    T m_ptr;
};