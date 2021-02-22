#ifndef WOLFSTEIN_INVALIDMAPEXCEPTION_H
#define WOLFSTEIN_INVALIDMAPEXCEPTION_H

#include <typeinfo>
#include <string>

class InvalidMapException : public std::exception {
private:
    std::string mensaje_error;
public:
    /*
      * creara la clase de invalidmap dejandola valida para uso
    */
    explicit InvalidMapException(const std::string &error) noexcept;
    /*
      * devuelve el error
    */
    virtual const char *what() const noexcept;
    /*
      * liberara a la clase
    */  
    virtual ~InvalidMapException() noexcept;
};

#endif //WOLFSTEIN_INVALIDMAPEXCEPTION_H
