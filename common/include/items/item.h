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

    bool estaCerca(int &posx, int &posy) {
        return this->posicion.estaCerca(posx, posy);
    }

private:
    Posicion posicion;
};

#endif
