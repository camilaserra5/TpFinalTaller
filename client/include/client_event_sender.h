#ifndef CLIENT_EVENT_SENDER_H
#define CLIENT_EVENT_SENDER_H

#include <string>
#include <vector>

#include "thread.h"
#include "socket.h"
#include "blocking_queue.h"
#include "comandos/comando.h"

class ClientEventSender : public Thread {
private:
    Socket &socket;

    bool running = true;

public:
    ClientEventSender(Socket &socket);

    void run() override;

    void cerrar();

    ~ClientEventSender();
};

#endif //CLIENT_EVENT_SENDER_H
