#ifndef ACTUALIZACION_INICIO_PARTIDA_H
#define ACTUALIZACION_INICIO_PARTIDA_H


#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"
#include "estadoJuego.h"

class ActualizacionInicioPartida : public Actualizacion {
public:
    ActualizacionInicioPartida() {}

    ActualizacionInicioPartida(std::vector<char>& informacion);

    ~ActualizacionInicioPartida();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    int obtenerId() override { return static_cast<int>(Accion::empezoPartida); }

    EstadoJuego &obtenerEstadoJuego();

private:
    std::vector<char> informacion;
    EstadoJuego estadoJuego;
};

#endif
