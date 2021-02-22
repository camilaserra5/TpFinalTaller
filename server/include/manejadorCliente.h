#ifndef _MANEJADOR_CLIENTES_H
#define _MANEJADOR_CLIENTES_H

#include "server_event_sender.h"
#include "server_event_receiver.h"
#include "objetosJuego.h"
#include "socket_error.h"

class ManejadorCliente {
public:
    ManejadorCliente(ProtectedQueue<Comando *> &comandos,
                     Protocolo *protocolo, int &id) {
        this->enviador = new Server_Event_Sender(protocolo);
        this->recibidor = new Server_Event_Receiver(comandos, protocolo);
        this->id = id;//no lo necesita porq se settea
        this->protocolo = protocolo;
    }

    ~ManejadorCliente() {

    }

    void run() {
        try {
            std::chrono::milliseconds duration(100);
            std::this_thread::sleep_for(duration);
            std::vector<char> empece(4);
            unsigned int size = htonl(static_cast<int>(Accion::empezoPartida));
            memcpy(empece.data(), &size, 4);
            this->protocolo->enviar(empece);
            std::this_thread::sleep_for(duration);
            this->enviador->start();
            this->recibidor->start();
        } catch (SocketError &e) {
            if (this->enviador->empezo()) {
                this->enviador->cerrar();
            } else if (this->recibidor->empezo()) {
                this->recibidor->cerrar();
            }
        }
    }

    void settearId(int &id) {
        this->id = id;
    }

    void join() {
        this->enviador->join();
        this->recibidor->join();
    }

    void enviar_actualizaciones(std::vector<Actualizacion *> actualizaciones) {
        this->enviador->enviar_actualizaciones(actualizaciones);
    }

    bool termino() {
        bool resultado = false;
        if (this->enviador->termino() || this->recibidor->termino()) {
            resultado = true;
        }
        return resultado;
    }

    void cerrar() {
        this->enviador->cerrar();
        this->recibidor->cerrar();
    }


private:
    Server_Event_Sender *enviador;
    Server_Event_Receiver *recibidor;
    Protocolo *protocolo;
    int id;
};

#endif
