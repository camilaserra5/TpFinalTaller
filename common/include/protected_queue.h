#ifndef  _PROTECTED_QUEUE_
#define _PROTECTED_QUEUE_

#include <queue>
#include <mutex>
#include <exception>
#include <iostream>

class QueueException : public std::exception {
private:
    std::string error;
public:
    /*
      * creara la excepcion de la cola
    */
    explicit QueueException(const std::string &error) :
            error(error) {}
    //const std::string getError() const { return this->error;}
};

template<class T>
class ProtectedQueue {
private:
    std::queue<T> cola_datos;
    std::mutex m;
public:
    /*
      * creara la cola protegida dejandola valida para uso
    */
    ProtectedQueue() {}
    /*
      * libera la cola protegida
    */
    ~ProtectedQueue() {}
    /*
      * si hay elements en la cola devuelve el elemnto sino lanza uan
      * exception
    */
    T obtener_dato() {
        std::lock_guard<std::mutex> l(this->m);
        if (this->cola_datos.empty()) {
            throw QueueException("no hay elementos en la cola\n");
        }
        T objeto = this->cola_datos.front();
        this->cola_datos.pop();
        return objeto;
    }
    /*
      * agrega un dato a la cola
    */        
    void aniadir_dato(T objeto) {
        std::lock_guard<std::mutex> l(this->m);
        this->cola_datos.push(objeto);
    }

};

#endif
