#ifndef  _PROTECTED_QUEUE_
#define _PROTECTED_QUEUE_

#include <queue>
#include <mutex>
#include <exception>
#include <iostream>
#include <condition_variable>

template<class T>
class BlockingQueue {
private:
    std::queue<T> cola_datos;
    std::mutex m;
    std::condition_variable esta_vacia;

public:
    BlockingQueue() {}

    ~BlockingQueue() {}

    void push(T objeto) {
        std::lock_guard<std::mutex> l(this->m);
        this->cola_datos.push(objeto);
        esta_vacia.notify_all();
    }

    T pop() {
        std::lock_guard<std::mutex> l(this->m);
        while(cola_datos.empty()) {
            esta_vacia.wait(this->m);
        }
        T objeto = this->cola_datos.front();
        this->cola_datos.pop();
        return objeto;
    }

};

#endif
