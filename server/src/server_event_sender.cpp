#include "../include/server_event_sender.h"

#include <sstream>

void Server_Event_Sender::run() {
    while (this->corriendo) {
        try {
            Actualizacion *actualizacion = this->actualizaciones.pop();
            std::vector<char> informacion = actualizacion->serializar();
            //protocolo.enviar(informacion);
        } catch (...) {
            this->corriendo = false;
        }
    }
}
