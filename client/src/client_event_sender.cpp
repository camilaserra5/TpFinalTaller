#include "../include/client_event_sender.h"
#include "socket.h"

#include <utility>
#include <algorithm>
#include <vector>
#include "protocolo.h"
#include <sstream>

ClientEventSender::ClientEventSender(Protocolo *protocolo,
                                     BlockingQueue<Comando *> &events) :
        events(events), corriendo(true), protocolo(protocolo) {}

void ClientEventSender::run() {
    while (this->corriendo) {
        try {
            Comando *evento = this->events.pop();
            std::vector<char> informacion = evento->serializar();
            protocolo->enviar(informacion);
        } catch (std::exception &exc) {
            std::cout << exc.what() << std::endl;
            this->corriendo = false;
        }
    }
}

void ClientEventSender::cerrar() {
    this->corriendo = false;
}

ClientEventSender::~ClientEventSender() {}
