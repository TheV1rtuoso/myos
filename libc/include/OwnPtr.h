#include <SmartPtr.h>


template<class T>
class OwnPtr {

    OwnPtr(T* pointee) : m_pointee(pointee) {}

    ~OwnPtr() {
        delete m_pointee;
    }

private:
    T* m_pointee;

};
