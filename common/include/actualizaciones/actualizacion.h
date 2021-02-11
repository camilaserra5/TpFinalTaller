#ifndef ACTUALIZACION_H
#define ACTUALIZACION_H

#include "estadoJuego.h"
#include <list>
#include "iserializable.h"
#include "ranking.h"

class Actualizacion : public ISerializable {
public:
    Actualizacion();

    ~Actualizacion();

    Actualizacion(EstadoJuego &estadoJuego);


    EstadoJuego &obtenerEstadoJuego();

    std::vector<int> obtenerRanking();

    bool terminoPartida();

private:
    EstadoJuego estadoJuego;
    std::vector<int> rankingJugadores;
    bool termine;
};

#endif
