#ifndef ACTUALIZACION_TERMINO_H
#define ACTUALIZACION_TERMINO_H


#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"
#include "estadoJuego.h"


class ActualizacionTerminoPartida : public Actualizacion {
public:
    ActualizacionTerminoPartida(EstadoJuego &estadoJuego);

    ActualizacionTerminoPartida() {}

    ~ActualizacionTerminoPartida();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    int obtenerId() override { return static_cast<int>(Accion::terminoPartida); }

    EstadoJuego &obtenerEstadoJuego() {
        return this->estadoJuego;
    }

private:
    EstadoJuego estadoJuego;
};

#endif
