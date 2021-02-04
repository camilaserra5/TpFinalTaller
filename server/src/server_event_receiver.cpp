#include "../include/server_event_receiver.h"
#include <vector>


void Server_Event_Receiver::run() {

    while (this->corriendo) {
        try {
            std::vector<char> informacion; /*this->protocolo.recibir()*/;
            Comando *comando = protocolo.deserializarComando(informacion);
            this->comandos.aniadir_dato(comando);

        } catch (...) {
            this->corriendo = false;
        }
    }
}
