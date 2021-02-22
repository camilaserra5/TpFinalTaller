#ifndef _MANEJADOR_CLIENTES_H
#define _MANEJADOR_CLIENTES_H

#include "server_event_sender.h"
#include "server_event_receiver.h"
#include "objetosJuego.h"
#include "socket_error.h"

class ManejadorCliente {
public:
    /*
      * creara la clase manejador de cliente dejandola valida para uso
      * tanto como el porotocolo como la cola de cmandos  deben estar
      * inicalizados
    */
    ManejadorCliente(ProtectedQueue<Comando *> &comandos,
                     Protocolo *protocolo, int &id) {
        this->enviador = new Server_Event_Sender(protocolo);
        this->recibidor = new Server_Event_Receiver(comandos, protocolo);
        this->id = id;
        this->protocolo = protocolo;
    }
    /*
      * Liberara a la clase
    */
    ~ManejadorCliente() {

    }
    /*
      * lanza a los dos hilos enviador y recibidor
    */
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
    /*
      * settea el id
    */
    void settearId(int &id) {
        this->id = id;
    }
    /*
      * hace join de los dos hilos
    */
    void join() {
        this->enviador->join();
        this->recibidor->join();
    }
    /*
      * envia las actualizaciones a los clientes
    */
    void enviar_actualizaciones(std::vector<Actualizacion *> actualizaciones) {
        this->enviador->enviar_actualizaciones(actualizaciones);
    }
    /*
      * devuelve true si alguno de los dos hilos termino sino false
    */
    bool termino() {
        bool resultado = false;
        if (this->enviador->termino() || this->recibidor->termino()) {
            resultado = true;
        }
        return resultado;
    }
    /*
      * cierra a los dos hilos
    */
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
