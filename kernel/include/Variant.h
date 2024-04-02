

template <typename _T1, typename _T2>
class Variant
{
public:
    Variant() = default;
    Variant(Variant &&) = default;
    Variant(const Variant &) = default;
    Variant &operator=(Variant &&) = default;
    Variant &operator=(const Variant &) = default;
    ~Variant() = default;

    bool hasValue() {
        return is_type_t1;
    }



private:
union
{
    _T1 val1;
    _T2 val2;
};

bool is_type_t1;
};
