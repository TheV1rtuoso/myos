class Error
{
public:
    Error() = default;
    Error(Error &&) = default;
    Error(const Error &) = default;
    Error &operator=(Error &&) = default;
    Error &operator=(const Error &) = default;
    ~Error() = default;
private:

};



using ErrorType = Error;

template <typename T>
class Result {
public:
    // Constructors to initialize a result with a value or an error
    Result(const T& value) : result_(value) {}
    Result(const ErrorType& error) : result_(error) {}

    // Check if the result contains a value
    bool hasValue() const {
        return std::holds_alternative<T>(result_);
    }

    // Get the value, assuming it exists
    T getValue() const {
        if (hasValue()) {
            return std::get<T>(result_);
        }
        throw std::logic_error("No value present");
    }

    // Get the error, assuming there is one
    ErrorType getError() const {
        if (!hasValue()) {
            return std::get<ErrorType>(result_);
        }
        throw std::logic_error("No error present");
    }

private:
    std::variant<T, ErrorType> result_;
};
