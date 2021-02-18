#ifndef WOLFSTEIN_INVALIDMAPEXCEPTION_H
#define WOLFSTEIN_INVALIDMAPEXCEPTION_H

#include <typeinfo>
#include <string>

class InvalidMapException : public std::exception {
private:
    std::string mensaje_error;
public:
    explicit InvalidMapException(const std::string &error) noexcept;

    virtual const char *what() const noexcept;

    virtual ~InvalidMapException() noexcept;
};

#endif //WOLFSTEIN_INVALIDMAPEXCEPTION_H
