#ifndef CLIENT_EVENT_SENDER_H
#define CLIENT_EVENT_SENDER_H

#include <string>
#include <vector>
#include <actualizacion.h>

#include "thread.h"
#include "socket.h"
#include "blocking_queue.h"
#include "comandos/comando.h"
#include "protocolo.h"

class ClientEventSender : public Thread {
private:
    Socket &socket;
    BlockingQueue<Comando *> &events;
    bool running = true;
    Protocolo protocolo;

public:
    ClientEventSender(Socket &socket, BlockingQueue<Comando *> &events);

    void run() override;

    void cerrar();

    ~ClientEventSender();
};

#endif //CLIENT_EVENT_SENDER_H
