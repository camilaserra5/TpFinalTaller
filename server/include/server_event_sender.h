#ifndef _SERVER_EVENT_SENDER_H
#define _SERVER_EVENT_SENDER_H


#include "thread.h"
#include "blocking_queue.h"
#include "socket.h"
#include "actualizaciones/actualizacion.h"
#include "protocolo.h"
#include <atomic>


class Server_Event_Sender : public Thread {
public:
    Server_Event_Sender(Protocolo *protocolo) : protocolo(protocolo), corriendo(true) {}

    ~Server_Event_Sender() {}

    void run() override;

    void cerrar();

    void enviar_actualizaciones(std::vector<Actualizacion *> act);

    bool estaCorriendo();

private:
    BlockingQueue<Actualizacion *> actualizaciones;
    Protocolo *protocolo;
    std::atomic<bool> corriendo;
};

#endif
