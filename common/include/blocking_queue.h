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
    /*
      * creara la cola bloquenate dejandola valida para uso
    */
    BlockingQueue() : esta_cerrado(false) {}
    /*
      * liberara la cola bloquenate con sus recursos
    */
    ~BlockingQueue() {}
    /*
      * agregara un elemento a la cola
    */
    void push(T objeto) {
        std::unique_lock<std::mutex> l(this->m);
        this->cola_datos.push(objeto);
        esta_vacia.notify_all();
    }
    /*
      * sacara un elemento de la cola si es que hay y no esta cerrada.
      * si nohay se queda esperando hasta que alla un elemento
    */
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
    /*
      * cierra la cola y le avisa a todos
    */   
    void cerrar() {
        this->esta_cerrado = true;
        esta_vacia.notify_all();
    }

};

#endif
