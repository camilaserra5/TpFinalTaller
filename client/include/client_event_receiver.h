#ifndef CLIENT_EVENT_RECEIVER_H
#define CLIENT_EVENT_RECEIVER_H

#include <string>
#include <vector>
#include <actualizacion.h>

#include "thread.h"
#include "socket.h"
#include "protected_queue.h"
#include "comandos/comando.h"
#include "modelo.h"

class ClientEventReceiver : public Thread {
private:
    Socket &socket;
    Modelo &modelo;
    ProtectedQueue<Actualizacion*> &updates;
    bool running = true;

public:
    ClientEventReceiver(Socket &socket, ProtectedQueue<Actualizacion *> &updates, Modelo& modelo);

    void run() override;

    void cerrar();

    ~ClientEventReceiver();
};

#endif //CLIENT_EVENT_RECEIVER_H
