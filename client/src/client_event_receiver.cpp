#include "../include/client_event_receiver.h"
#include "socket.h"
#include "map.h"
#include "items/item.h"
#include "jugador.h"
#include "estadoJuego.h"
#include "actualizaciones/actualizacion.h"

#include <utility>
#include <algorithm>
#include <vector>
#include <map>

#include <actualizaciones/actualizacionInicioPartida.h>
#include <actualizaciones/actualizacionCambioArma.h>
#include <actualizaciones/actualizacionAtaque.h>
#include <actualizaciones/actualizacionAperturaPuerta.h>
#include <actualizaciones/actualizacionMovimiento.h>
#include <actualizaciones/actualizacionTerminoPartida.h>

ClientEventReceiver::ClientEventReceiver(Protocolo *protocolo,
                                         ProtectedQueue<Actualizacion *> &updates, Modelo &modelo, int idJugador) :

        protocolo(protocolo), updates(updates), modelo(modelo), idJugador(idJugador), corriendo(true) {}

Actualizacion *deserializarActualizacion(std::vector<char> informacion) {
    std::vector<char> sub(4);
    char number[4];
    sub = std::vector<char>(&informacion[0], &informacion[4]);
    memcpy(number, sub.data(), 4);
    uint32_t *buf = (uint32_t *) number;
    int idActualizacion = ntohl(*buf);
    std::vector<char> actualizacionSerializada(informacion.begin() + 4, informacion.end());
    if (idActualizacion == static_cast<int>(Accion::empezoPartida)) {
        auto act = new ActualizacionInicioPartida();
        act->deserializar(actualizacionSerializada);
        return act;
    } else if (idActualizacion == static_cast<int>(Accion::aperturaDePuerta)) {
        auto act = new ActualizacionAperturaPuerta();
        act->deserializar(actualizacionSerializada);
        return act;
    } else if (idActualizacion == static_cast<int>(Accion::cambioDeArma)) {
        auto act = new ActualizacionCambioArma();
        act->deserializar(actualizacionSerializada);
        return act;
    } else if (idActualizacion == static_cast<int>(Accion::ataque)) {
        auto act = new ActualizacionAtaque();
        act->deserializar(actualizacionSerializada);
        return act;
    } else if (idActualizacion == static_cast<int>(Accion::moverse)) {
        ActualizacionMovimiento *act = new ActualizacionMovimiento();
        act->deserializar(actualizacionSerializada);
        return act;
    } else if (idActualizacion == static_cast<int>(Accion::terminoPartida)) {
        auto act = new ActualizacionTerminoPartida();
        act->deserializar(actualizacionSerializada);
        return act;
    }
    return nullptr;
}

void ClientEventReceiver::run() {
    while (this->corriendo) {
        try {
            std::vector<char> informacion = this->protocolo->recibir();
            std::cerr << "meto actualizacion\n" << informacion.size() << "\n";
            if (!informacion.empty()) {
                Actualizacion *actualizacion = deserializarActualizacion(informacion);

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
