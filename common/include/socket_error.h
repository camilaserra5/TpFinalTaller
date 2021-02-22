#ifndef SOCKET_ERROR_H
#define SOCKET_ERROR_H

#include <typeinfo>
#include <string>

class SocketError : public std::exception {
private:
    std::string mensaje_error;
public:
    /*
      * Creara la clase Socket error dejandola valida para uso
    */
    explicit SocketError(const std::string &error) noexcept;
    /*
      * devuelve el error que ocurrio de socket
    */
    virtual const char *what() const noexcept;
    /*
      * liberara la clase
    */
    virtual ~SocketError() noexcept;
};

#endif /*SOCKET_ERROR_H*/
