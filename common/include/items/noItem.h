#ifndef NO_ITEM_H
#define NO_ITEM_H

#include "item.h"
#include <iostream>

class NoItem : public Item {
public:
    NoItem(Posicion &posicion) : Item(posicion) {}

    ~NoItem() {}

    void obtenerBeneficio(Jugador *jugador) override {
        std::cout << "beneficio de no item\n";
    }

};

#endif
