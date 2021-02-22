#ifndef CLIENT_EVENT_SENDER_H
#define CLIENT_EVENT_SENDER_H

#include <string>
#include <vector>
#include <actualizaciones/actualizacion.h>

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
    Protocolo *protocolo;

public:
    /*
      * creara a la clase client event sender dejandola valida para uso
      * tanto como el protocolo y la cola bloqueate deben estar inicializadas
    */
    ClientEventSender(Protocolo *protocolo, BlockingQueue<Comando *> &events);

    /*
      * sacara un comando de la cola de comandos, la serializara y la
      * enviara a travez del protocolo
    */
    void run() override;

    /*
      * cerrara el protocolo de comunacion
    */
    void cerrar();

    /*
      * liberera a la clase con todos sus recursos
    */
    ~ClientEventSender();
};

#endif //CLIENT_EVENT_SENDER_H
