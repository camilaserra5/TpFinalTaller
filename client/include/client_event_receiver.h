#ifndef CLIENT_EVENT_RECEIVER_H
#define CLIENT_EVENT_RECEIVER_H

#include <string>
#include <vector>
#include <actualizaciones/actualizacion.h>

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
    /*
      * creara la clase cliente Event receiver dejandola valida para uso
      * tanto como el protocolo, la protected_queue, el modeloy el idJugador
      * deben estar inicialiados/validos
    */
    ClientEventReceiver(Protocolo *protocolo, ProtectedQueue<Actualizacion *> &updates,
                        Modelo &modelo, int idJugador);

    /*
      * recibira un vector de caracteres por medio del protocolo y encolara
      * una atualizacion en la cola protegida
    */
    void run() override;

    /*
      * cerrara el protocolo de comunicacion
    */
    void cerrar();

    /*
      * liberara la clase client event reciber con sus recursos
    */
    ~ClientEventReceiver();

    /*
      * determina si recibio
    */
    bool recibi() {
        return this->recibii;
    }
};

#endif //CLIENT_EVENT_RECEIVER_H
