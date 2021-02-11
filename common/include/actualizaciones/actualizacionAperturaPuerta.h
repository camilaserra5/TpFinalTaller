#ifndef ACTUALIZACION_PUERTA_H
#define ACTUALIZACION_PUERTA_H

#include "estadoJuego.h"
#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"

class ActualizacionAperturaPuerta : public Actualizacion {
public:
    ActualizacionAperturaPuerta();

    ~ActualizacionAperturaPuerta();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

private:
};

#endif
