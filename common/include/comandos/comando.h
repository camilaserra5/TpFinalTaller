#ifndef COMANDO_H
#define COMANDO_H

#include <iostream>
#include <actualizaciones/actualizacion.h>
#include "estadoJuego.h"
#include "iserializable.h"

class Comando : public ISerializable {
public:
    Comando(int idJugador);

    virtual ~Comando() {}

    Comando();

    virtual std::vector<Actualizacion *> ejecutar(EstadoJuego &estadoJuego) = 0;


protected:
    int idJugador;
};

#endif
