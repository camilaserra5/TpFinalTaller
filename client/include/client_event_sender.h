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
#include <atomic>

class ClientEventSender : public Thread {
private:

    BlockingQueue<Comando *> &events;
    std::atomic<bool> corriendo;
    Protocolo* protocolo;

public:
    ClientEventSender(Protocolo* protocolo, BlockingQueue<Comando *> &events);

    void run() override;

    void cerrar();

    ~ClientEventSender();
};

#endif //CLIENT_EVENT_SENDER_H
