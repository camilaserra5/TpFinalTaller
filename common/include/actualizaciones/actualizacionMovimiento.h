#ifndef ACTUALIZACION_MOV_H
#define ACTUALIZACION_MOV_H

#include "estadoJuego.h"
#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"

class ActualizacionMovimiento : public Actualizacion {
public:
    ActualizacionMovimiento() {}

    ActualizacionMovimiento(Jugador *jugador);

    ~ActualizacionMovimiento();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    int obtenerId() override { return static_cast<int>(Accion::moverse); }

private:
};

#endif
