#ifndef ACTUALIZACION_CambioArma_H
#define ACTUALIZACION_CambioArma_H

#include "estadoJuego.h"
#include <list>
#include "iserializable.h"
#include "ranking.h"
#include "actualizacion.h"

class ActualizacionCambioArma : public Actualizacion {
public:
    ActualizacionCambioArma();

    ~ActualizacionCambioArma();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    int obtenerId() override { return static_cast<int>(Accion::cambioDeArma); }

private:
};

#endif
