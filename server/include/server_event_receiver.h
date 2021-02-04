#ifndef _SERVER_EVENT_RECEIVER
#define _SERVER_EVENT_RECEIVER

#include "thread.h"
#include "protected_queue.h"
#include "socket.h"
#include "comandos/comando.h"
#include "protocolo.h"
#include <atomic>

class Server_Event_Receiver : public Thread {
public:
    Server_Event_Receiver(ProtectedQueue<Comando *> &comandos, Socket &socket) :
            comandos(comandos), protocolo(std::move(socket)), corriendo(true) {}

    ~Server_Event_Receiver() {}

    void run() override;

    void cerrar() {
        this->corriendo = false;
    }

private:
    ProtectedQueue<Comando *> &comandos;
    Protocolo protocolo;
    std::atomic<bool> corriendo;

};

#endif
