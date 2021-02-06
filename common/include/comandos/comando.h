#ifndef COMANDO_H
#define COMANDO_H

#include <iostream>
#include "estadoJuego.h"
#include "iserializable.h"

class Comando : public ISerializable {
public:
    Comando(int idJugador);

    virtual ~Comando() {}

    Comando();

    virtual void ejecutar(EstadoJuego &estadoJuego) = 0;


protected:
    int idJugador;
};

#endif
