#include "../include/server_event_receiver.h"
#include "socket_error.h"

void Server_Event_Receiver::run() {
    while (this->corriendo) {
        try {
            std::vector<char> informacion = this->protocolo->recibir();
<<<<<<< HEAD
            std::cerr << "comando size:  " << informacion.size() << std::endl;
            Comando *comando = protocolo->deserializarComando(informacion);
            this->comandos.aniadir_dato(comando);
        }catch (const SocketError& exc){
            std::cerr << "error en server recibier\n";
            std::cout << exc.what() << std::endl;
            this->cerrar();
=======
            if (informacion.empty()) {
                this->cerrar();
            } else {
                std::cerr << "comando size:  " << informacion.size() << std::endl;
                Comando *comando = protocolo->deserializarComando(informacion);
                this->comandos.aniadir_dato(comando);
            }
>>>>>>> 0fc9e59f0849ab6be23f77097005aecaf12a9b57
        } catch (std::exception &exc) {
            std::cout << exc.what() << std::endl;
            this->cerrar();
        }
    }
}
