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

    T obtener_comando();

    void aniadir_comando(T objeto);
};//pasar a una cla protegida que tiene objetos del tipo ISerializable
#endif
