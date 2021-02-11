#ifndef ACTUALIZACION_INICIO_PARTIDA_H
#define ACTUALIZACION_INICIO_PARTIDA_H

#include "estadoJuego.h"
#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"

class ActualizacionInicioPartida : public Actualizacion {
public:
    ActualizacionInicioPartida();

    ~ActualizacionInicioPartida();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

private:
};

#endif
