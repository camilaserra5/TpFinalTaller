#ifndef _SERVER_EVENT_SENDER_H
#define _SERVER_EVENT_SENDER_H


#include "thread.h"
#include "blocking_queue.h"
#include "socket.h"
#include "actualizacion.h"
#include "protocolo.h"
#include <atomic>


class Server_Event_Sender : public Thread {
public:
    Server_Event_Sender(Protocolo* protocolo) : protocolo(protocolo), corriendo(true) {}

    ~Server_Event_Sender() {}

    void run() override;

    void cerrar() {
        this->corriendo = false;
    }

    void enviar_actualizaciones(Actualizacion* actualizacion){
      this->actualizaciones.push(actualizacion);
    }

private:
    BlockingQueue<Actualizacion *> actualizaciones;
    Protocolo* protocolo;
    std::atomic<bool> corriendo; // deberian ser atomic??
};

#endif
