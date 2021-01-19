#include "../include/client_event_sender.h"
#include "socket.h"

#include <utility>
#include <algorithm>
#include <vector>

ClientEventSender::ClientEventSender(Socket &socket,
                                     BlockingQueue<Comando *> &events) :
        socket(socket), events(events) {}

void ClientEventSender::run() {
    while (this->running) {
        //Comando *event = this->events.pop();
        // debería ser protocolo en lugar de socket?
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