#include "../include/client_event_sender.h"
#include "socket.h"

#include <utility>
#include <algorithm>
#include <vector>
#include "protocolo.h"

ClientEventSender::ClientEventSender(Socket &socket,
                                     BlockingQueue<Comando *> &events) :
        socket(socket), events(events), protocolo(std::move(socket)) {}

void ClientEventSender::run() {
    while (this->running) {
        Comando *evento = this->events.pop();
        // debería ser protocolo en lugar de socket?
        protocolo.enviar(evento);
        //this->socket.enviar(evento);
    }
}

void ClientEventSender::cerrar() {
    this->running = false;
}

ClientEventSender::~ClientEventSender() {
    this->running = false;
    this->join();
}
