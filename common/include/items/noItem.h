#ifndef NO_ITEM_H
#define NO_ITEM_H

#include "item.h"
#include <iostream>

class NoItem : public Item {
public:
    NoItem(Posicion &posicion, int id) : Item(posicion, id) {}

    ~NoItem() {}

    void obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) override {
        std::cout << "beneficio de no item\n";
    }

    Type getTipo() override{
        return Type::noItem;
    }

};

#endif
