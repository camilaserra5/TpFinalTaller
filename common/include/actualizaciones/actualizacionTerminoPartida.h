#ifndef ACTUALIZACION_TERMINO_H
#define ACTUALIZACION_TERMINO_H

#include "estadoJuego.h"
#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"

class ActualizacionTerminoPartida : public Actualizacion {
public:
    ActualizacionTerminoPartida();

    ~ActualizacionTerminoPartida();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    int obtenerId() override { return static_cast<int>(Accion::terminoPartida); }

    std::vector<int> obtenerRanking();

private:
};

#endif
