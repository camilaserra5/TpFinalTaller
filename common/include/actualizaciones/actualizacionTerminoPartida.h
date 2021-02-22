#ifndef ACTUALIZACION_TERMINO_H
#define ACTUALIZACION_TERMINO_H


#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"
#include "jugador.h"
#include <map>


class ActualizacionTerminoPartida : public Actualizacion {
public:
    ActualizacionTerminoPartida(std::map<int, Jugador*> jugadores );

    ActualizacionTerminoPartida() {}

    ~ActualizacionTerminoPartida();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    int obtenerId() override { return static_cast<int>(Accion::terminoPartida); }

    std::map<int, Jugador*> &obtenerJugadores() {
        return this->jugadores;
    }

private:
    std::map<int, Jugador*> jugadores;
};

#endif
