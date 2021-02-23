#include "../include/client_event_sender.h"

#include <algorithm>
#include "socket_error.h"

ClientEventSender::ClientEventSender(Protocolo *protocolo, BlockingQueue<Comando *> &events) :
        events(events), corriendo(true), protocolo(protocolo) {}

void ClientEventSender::run() {
    while (this->corriendo) {
        try {
            Comando *evento = this->events.pop();
            std::vector<char> informacion = evento->serializar();
            protocolo->enviar(informacion);
            delete evento;
        } catch (const SocketError &exc) {
            std::cout << exc.what() << std::endl;
            this->cerrar();
            std::cerr << "senderr\n";
        } catch (std::exception &exc) {

            std::cout << exc.what() << std::endl;
            std::cerr << "senderr\n";

            this->cerrar();
        }
    }
    std::cerr<< "CORTO EJECUCION DE SENDER\n";

}

void ClientEventSender::cerrar() {
        this->corriendo = false;
        this->protocolo->cerrar();
        this->events.cerrar();
}

ClientEventSender::~ClientEventSender() {}
