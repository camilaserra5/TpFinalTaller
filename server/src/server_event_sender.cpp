#include "../include/server_event_sender.h"

#include "socket_error.h"

void Server_Event_Sender::run() {
    while (this->corriendo) {
        try {
            Actualizacion *actualizacion = this->actualizaciones.pop();
            std::vector<char> informacion = actualizacion->serializar();
            protocolo->enviar(informacion);
<<<<<<< HEAD

        }catch (const SocketError& exc){
                std::cerr << "error en server recibier\n";
                std::cout << exc.what() << std::endl;
                this->cerrar();
=======
        } catch (const SocketError &exc) {
            std::cout << exc.what() << std::endl;
            this->cerrar();
>>>>>>> 0fc9e59f0849ab6be23f77097005aecaf12a9b57
        } catch (std::exception &exc) {
            std::cout << exc.what() << std::endl;
            this->cerrar();
        }

    }
}
