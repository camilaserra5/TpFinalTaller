#include "../include/server_event_receiver.h"
#include <vector>
#include "socket_error.h"

void Server_Event_Receiver::run() {
    while (this->corriendo) {
        try {
            std::vector<char> informacion = this->protocolo->recibir();
            std::cerr << "comando size:  " << informacion.size() << std::endl;
            Comando *comando = protocolo->deserializarComando(informacion);
            this->comandos.aniadir_dato(comando);
        }catch (const SocketError& exc){
            std::cout << exc.what() << std::endl;
            this->cerrar();
        } catch (std::exception &exc) {
            std::cout << exc.what() << std::endl;
            this->cerrar();
        }
    }
}
