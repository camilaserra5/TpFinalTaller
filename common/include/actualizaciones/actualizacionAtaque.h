#ifndef ACTUALIZACION_ATAQUE_H
#define ACTUALIZACION_ATAQUE_H

#include "estadoJuego.h"
#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"

class ActualizacionAtaque : public Actualizacion {
public:
    ActualizacionAtaque();

    ~ActualizacionAtaque();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

private:
};

#endif
