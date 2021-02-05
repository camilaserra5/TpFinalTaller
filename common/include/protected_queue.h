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
    ProtectedQueue(){}

    ~ProtectedQueue(){}

    T obtener_dato() {
        std::lock_guard<std::mutex> l(this->m);
        if (this->cola_datos.empty()) {
            throw QueueException("no hay elementos en la cola\n");
        }
        T objeto = this->cola_datos.front();
        this->cola_datos.pop();
        return objeto;
    }

    void aniadir_dato(T objeto) {
        std::lock_guard<std::mutex> l(this->m);
        this->cola_datos.push(objeto);
    }

};

#endif
