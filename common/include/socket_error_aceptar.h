#ifndef SOCKET_ERROR_ACEPTAR_H
#define SOCKET_ERROR_ACEPTAR_H

#include <typeinfo>

class SocketErrorAceptar : public std::exception {
public:
    /*
      * Creara la clase de socket error al acpetar  dejandola valida para uso
    */
    SocketErrorAceptar();
    /*
      * liberara la clase 
    */
    virtual~SocketErrorAceptar() noexcept;
};

#endif /*SOCKET_ERROR_ACEPTAR_H*/
