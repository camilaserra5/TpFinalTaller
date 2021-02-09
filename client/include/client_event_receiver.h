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
#include "protocolo.h"
#include <atomic>


class ClientEventReceiver : public Thread {
private:
    Protocolo *protocolo;
    Modelo &modelo;
    ProtectedQueue<Actualizacion *> &updates;
    std::atomic<bool> corriendo;
    int idJugador;
    bool recibii = false;

public:
    ClientEventReceiver(Protocolo *protocolo, ProtectedQueue<Actualizacion *> &updates,
                        Modelo &modelo, int idJugador);

    void run() override;

    void cerrar();

    ~ClientEventReceiver();

    bool recibi(){
      return this->recibii;
    }
};

#endif //CLIENT_EVENT_RECEIVER_H
