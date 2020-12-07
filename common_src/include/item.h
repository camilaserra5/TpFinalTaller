#ifndef ITEM_H
#define ITEM_H
#include "jugador.h"

class Item{
  public:
    Item(){}
    virtual ~Item(){}
    virtual void obtenerBeneficio(Jugador &jugador) = 0;
};

#endif
