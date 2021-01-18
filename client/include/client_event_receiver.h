#ifndef CLIENT_EVENT_RECEIVER_H
#define CLIENT_EVENT_RECEIVER_H

#include <string>
#include <vector>

#include "thread.h"
#include "socket.h"
#include "protected_queue.h"
#include "comandos/comando.h"

class ClientEventReceiver : public Thread {
private:
    Socket &socket;
    //ProtectedQueue<Comando *> &updates;
    bool running = true;

public:
    ClientEventReceiver(Socket &socket/*, ProtectedQueue<Comando *> &updates*/);

    void run() override;

    void cerrar();

    ~ClientEventReceiver();
};

#endif //CLIENT_EVENT_RECEIVER_H
