#include "../include/client_event_sender.h"
#include "socket.h"

#include <utility>
#include <algorithm>
#include <vector>
#include "protocolo.h"
#include <sstream>

ClientEventSender::ClientEventSender(Protocolo* protocolo,
                                     BlockingQueue<Comando *> &events) :
        events(events), protocolo(protocolo) {}

void ClientEventSender::run() {
    while (this->running) {
        try{
            Comando *evento = this->events.pop();
            std::vector<char> informacion = evento->serializar();
            protocolo->enviar(informacion);
        }catch(...){
            this->running = false;
        }
    }
}

void ClientEventSender::cerrar() {
    this->running = false;
}

ClientEventSender::~ClientEventSender() {
    this->running = false;
    this->join();
}
