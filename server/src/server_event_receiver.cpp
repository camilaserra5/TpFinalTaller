#include "../include/server_event_receiver.h"
#include "socket_error.h"

void Server_Event_Receiver::run() {
    while (this->corriendo) {
        try {
            std::vector<char> informacion = this->protocolo->recibir();
            if (informacion.empty()) {
                this->cerrar();
            } else {
                std::cerr << "comando size:  " << informacion.size() << std::endl;
                Comando *comando = protocolo->deserializarComando(informacion);
                this->comandos.aniadir_dato(comando);
            }
        } catch (std::exception &exc) {
            std::cout << exc.what() << std::endl;
            this->cerrar();
        }
    }
}
