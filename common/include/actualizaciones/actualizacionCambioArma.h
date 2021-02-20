#ifndef ACTUALIZACION_CAMBIO_ARMA_H
#define ACTUALIZACION_CAMBIO_ARMA_H


#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"
#include "jugador.h"

class ActualizacionCambioArma : public Actualizacion {
public:
    ActualizacionCambioArma(int &id, int &armaActual);

    ActualizacionCambioArma() {}

    ~ActualizacionCambioArma();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    int obtenerId() override { return static_cast<int>(Accion::cambioDeArma); }

    int obtenerIdArma() {
        return armaActual;
    }

    int obtenerIdJugador() {
        return id;
    }

private:
    int id;
    int armaActual;
};

#endif
