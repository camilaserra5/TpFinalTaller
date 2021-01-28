#include "../include/server_event_receiver.h"
#include <sstream>


void Server_Event_Receiver::run() {

    while (this->corriendo) {
        try {
            std::stringstream informacion = this->protocolo.recibir();
            Comando *comando = protocolo.deserializarComando(informacion);
            this->comandos.aniadir_dato(comando);

        } catch (...) {
            this->corriendo = false;
        }
    }
}
