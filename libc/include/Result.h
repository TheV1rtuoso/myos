#include <assert.h>

class Error {

};

template <typename T, typename D>
class Variant {
public:
    Variant(T) : m_union(T) m_has_t(true) {}

    T getT()

private:
    union m_union
    {
        T t,
        D d
    };
    bool m_has_t;
};

template <typename T, typename E = Error>
class Result {
public:
    bool hasValue(){
        return m_result.m_has_t;
    }

    T get(){
        assert(hasValue);
        return m_result.
    }

private:
    Variant<T,E> m_result;
};