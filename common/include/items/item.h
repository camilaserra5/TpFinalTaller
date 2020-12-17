#ifndef ITEM_H
#define ITEM_H

#include "jugador.h"
#include "posicion.h"
#include "entidadPosicionable.h"

class Item : public EntidadPosicionable {
public:
    Item(Posicion &posicion) : posicion(posicion) {}

    virtual ~Item() {}

    virtual void obtenerBeneficio(Jugador *jugador) = 0;

private:
    Posicion posicion;
};

#endif
