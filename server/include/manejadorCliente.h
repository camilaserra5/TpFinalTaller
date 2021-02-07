#ifndef _MANEJADOR_CLIENTES_H
#define _MANEJADOR_CLIENTES_H

#include "server_event_sender.h"
#include "server_event_receiver.h"
#include "objetosJuego.h"

class ManejadorCliente {
public:
    ManejadorCliente(BlockingQueue<Actualizacion *> &actualizaciones, ProtectedQueue<Comando *> &comandos,
                     Protocolo *protocolo, int &id) {
        this->enviador = new Server_Event_Sender(actualizaciones, protocolo);
        this->recibidor = new Server_Event_Receiver(comandos, protocolo);
        this->id = id;//no lo necesita porq se settea
        this->protocolo = protocolo;
    }

    ~ManejadorCliente() {

    }

    void run() {
        std::vector<char> empece(4);
        unsigned int size = htonl(static_cast<int>(Accion::empezoPartida));
        memcpy(empece.data(), &size, 4);
        this->protocolo->enviar(empece);
        std::chrono::milliseconds duration(50);
        std::this_thread::sleep_for(duration);
        this->enviador->start();
        this->recibidor->start();
    }

    void settearId(int &id) {
        this->id = id;
    }

    void join() {
        this->enviador->join();
        this->recibidor->join();
    }

private:
    Server_Event_Sender *enviador;
    Server_Event_Receiver *recibidor;
    Protocolo *protocolo;
    int id;
};

#endif
