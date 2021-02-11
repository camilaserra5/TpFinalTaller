#include "../include/client_event_receiver.h"
#include "socket.h"
#include "map.h"
#include "items/item.h"
#include "jugador.h"
#include "estadoJuego.h"
#include "actualizacion.h"

#include <utility>
#include <algorithm>
#include <vector>
#include <map>

ClientEventReceiver::ClientEventReceiver(Protocolo *protocolo,
                                         ProtectedQueue<Actualizacion *> &updates, Modelo &modelo, int idJugador) :

        protocolo(protocolo), updates(updates), modelo(modelo), idJugador(idJugador), corriendo(true) {}

void ClientEventReceiver::run() {
    while (this->corriendo) {
        try {
            std::vector<char> informacion = this->protocolo->recibir();
            std::cerr << "meto actualizacion\n" << informacion.size() << "\n";
            if (!informacion.empty()) {
                Actualizacion *actualizacion = new Actualizacion();
                actualizacion->deserializar(informacion);
                this->updates.aniadir_dato(actualizacion);
                this->recibii = true;
            }
        } catch (std::exception &exc) {
            std::cout << exc.what() << std::endl;
            std::cerr << "fallooooooooo no recibo mas \n";

            this->corriendo = false;
        }
    }
}

void ClientEventReceiver::cerrar() {
    this->corriendo = false;
}

ClientEventReceiver::~ClientEventReceiver() {
    this->corriendo = false;
}
