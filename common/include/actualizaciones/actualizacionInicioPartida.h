#ifndef ACTUALIZACION_INICIO_PARTIDA_H
#define ACTUALIZACION_INICIO_PARTIDA_H

#include "estadoJuego.h"
#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"

class ActualizacionInicioPartida : public Actualizacion {
public:
    ActualizacionInicioPartida(EstadoJuego &estadoJuego);

    ~ActualizacionInicioPartida();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    int obtenerId() override { return static_cast<int>(Accion::empezoPartida); }

    EstadoJuego &obtenerEstadoJuego();

private:
    EstadoJuego estadoJuego;
    std::vector<int> rankingJugadores;
    bool termine;
};

#endif
