#ifndef  _PROTECTED_QUEUE_
#define _PROTECTED_QUEUE_

#include <queue>
#include <mutex>
#include <exception>

class QueueException : public std::exception {
private:
    std::string error;
public:
    explicit QueueException(const std::string &error) :
            error(error) {}
    //const std::string getError() const { return this->error;}
};

template <class T>
class ProtectedQueue {
private:
    std::queue<T> cola_comandos;
    std::mutex m;
public:
    ProtectedQueue(){}

    ~ProtectedQueue(){}

    T obtener_comando() {
        std::lock_guard <std::mutex> l(this->m);
        if (this->cola_comandos.empty()) {
            throw QueueException("no hay elementos en la cola\n");
        }
        T objeto = this->cola_comandos.front();
        this->cola_comandos.pop();
        return objeto;
    }

    void aniadir_comando(T objeto) {
        std::lock_guard <std::mutex> l(this->m);
        this->cola_comandos.push(objeto);
    }

/*
    T obtener_comando();

    void aniadir_comando(T objeto);*/
};

#endif
