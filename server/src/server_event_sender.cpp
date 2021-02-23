#include "../include/server_event_sender.h"

#include "socket_error.h"
#include "protected_queue.h"

void Server_Event_Sender::run() {
    while (this->corriendo) {
        try {
            Actualizacion *actualizacion = this->actualizaciones.pop();
            std::vector<char> informacion = actualizacion->serializar();
            protocolo->enviar(informacion);
        } catch (const SocketError &exc) {
            std::cout << exc.what() << std::endl;
            this->cerrar();
        } catch (std::exception &exc) {
            std::cout << exc.what() << std::endl;
            this->cerrar();
        } catch(...){
            std::cout << "error desconocido\n";
            this->cerrar();
        }

    }
}

void Server_Event_Sender::cerrar() {
    this->corriendo = false;
    protocolo->cerrar();
    this->actualizaciones.cerrar();
}

void Server_Event_Sender::enviar_actualizaciones(std::vector<Actualizacion *> act) {
    std::vector<Actualizacion *>::iterator it;
    for (it = act.begin(); it != act.end(); ++it) {
        this->actualizaciones.push(*it);
    }
}

bool Server_Event_Sender::estaCorriendo() {
    return corriendo;
}
