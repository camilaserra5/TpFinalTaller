#ifndef  _BLOCKING_QUEUE_
#define _BLOCKING_QUEUE_

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
        std::unique_lock<std::mutex> l(this->m);
        this->cola_datos.push(objeto);
        esta_vacia.notify_all();
    }

    T pop() {
        std::unique_lock<std::mutex> l(this->m);
        while (cola_datos.empty()) {
            esta_vacia.wait(l);
        }
        T objeto = this->cola_datos.front();
        this->cola_datos.pop();
        return objeto;
    }

};

#endif
