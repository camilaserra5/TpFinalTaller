#include "../include/protected_queue.h"

ProtectedQueue::ProtectedQueue() {

}

ProtectedQueue::~ProtectedQueue() {

}

Comando *ProtectedQueue::obtener_comando() {
    std::lock_guard <std::mutex> l(this->m);
    if (this->cola_comandos.empty()) {
        throw QueueException("no hay elementos en la cola\n");
    }
    Comando *comando = this->cola_comandos.front();
    this->cola_comandos.pop();
    return comando;
}

void ProtectedQueue::aniadir_comando(Comando *comando) {
    std::lock_guard <std::mutex> l(this->m);
    this->cola_comandos.push(comando);
}
