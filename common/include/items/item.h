#ifndef ITEM_H
#define ITEM_H

#include "jugador.h"
#include "posicion.h"

class Item {
public:
    Item(Posicion &posicion):posicion(posicion){}

    virtual ~Item() {}

    virtual void obtenerBeneficio(Jugador *jugador) = 0;

  private:
    Posicion posicion;
};

#endif
