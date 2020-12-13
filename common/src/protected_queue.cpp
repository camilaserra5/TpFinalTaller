#include "../include/protected_queue.h"

template <class T>
T ProtectedQueue<T>::obtener_comando() {
    std::lock_guard <std::mutex> l(this->m);
    if (this->cola_comandos.empty()) {
        throw QueueException("no hay elementos en la cola\n");
    }
    T objeto = this->cola_comandos.front();
    this->cola_comandos.pop();
    return objeto;
}
template <class T>
void ProtectedQueue<T>::aniadir_comando(T objeto) {
    std::lock_guard <std::mutex> l(this->m);
    this->cola_comandos.push(objeto);
}
