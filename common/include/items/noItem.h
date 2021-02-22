#ifndef NO_ITEM_H
#define NO_ITEM_H

#include "item.h"
#include <iostream>

class NoItem : public Item {
public:
    /*
      * creara la clase no Item dejandola valida para uso
    */
    NoItem(Posicion &posicion, int id) : Item(posicion, id) {}
    /*
      *liberara la clase con sus recursos
    */
    ~NoItem() {}
    /*
      * devulve true si pudo obtener el beneficio sino false
    */
    bool obtenerBeneficio(Jugador *jugador) override {
        return false;
    }
    /*
      * devuelve el tipo de item
    */  
    Type getTipo() override {
        return ObjetosJuego::obtenerTipoPorNombre("noItem");
    }

};

#endif
