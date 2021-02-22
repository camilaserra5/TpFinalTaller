#ifndef  _BLOCKING_QUEUE_
#define _BLOCKING_QUEUE_

#include <queue>
#include <mutex>
#include <exception>
#include <iostream>
#include <condition_variable>
#include "protected_queue.h"
#include <atomic>

template<class T>
class BlockingQueue {
private:
    std::queue<T> cola_datos;
    std::mutex m;
    std::condition_variable esta_vacia;
    std::atomic<bool> esta_cerrado;

public:
    BlockingQueue() : esta_cerrado(false) {}

    ~BlockingQueue() {}

    void push(T objeto) {
        std::unique_lock<std::mutex> l(this->m);
        this->cola_datos.push(objeto);
        esta_vacia.notify_all();
    }

    T pop() {
        std::unique_lock<std::mutex> l(this->m);
        while (cola_datos.empty() && !esta_cerrado) {
            esta_vacia.wait(l);
        }
        if (esta_cerrado) {
            throw QueueException("no hay elementos en la cola\n");
        }
        T objeto = this->cola_datos.front();
        this->cola_datos.pop();
        return objeto;
    }

    void cerrar() {
        this->esta_cerrado = true;
        esta_vacia.notify_all();
    }

};

#endif
