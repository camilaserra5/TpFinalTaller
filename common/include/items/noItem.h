#ifndef NO_ITEM_H
#define NO_ITEM_H

#include "item.h"
#include <iostream>

class NoItem : public Item {
public:
    NoItem(Posicion &posicion, int id) : Item(posicion, id) {}

    ~NoItem() {}

    bool obtenerBeneficio(Jugador *jugador) override{
        return false;
    }

    Type getTipo() override{
        return Type::noItem;
    }

};

#endif
