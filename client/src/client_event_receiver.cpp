#include "../include/client_event_receiver.h"
#include "socket.h"

#include <utility>
#include <algorithm>
#include <vector>

ClientEventReceiver::ClientEventReceiver(Socket &socket,
                                         ProtectedQueue<Actualizacion *> &updates) :

        socket(socket), updates(updates) {}

void ClientEventReceiver::run() {
    while (this->running) {
        Actualizacion *update;
        // debería ser un protocolo en realidad
        //this->socket.recibir();
        //this->updates.aniadir_dato(update);
    }
}

void ClientEventReceiver::cerrar() {
    this->running = false;
}

ClientEventReceiver::~ClientEventReceiver() {
    this->running = false;
    this->join();
}