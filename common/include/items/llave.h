#ifndef LLAVE_H
#define LLAVE_H


#include "item.h"

class Llave : public Item {
public:
    // esta llave es la misma para todas las puerta no hay una llave por puerta;
    //llave magica
    Llave(Posicion &posicion, int id) : Item(posicion, id) {}

    ~Llave();

    void obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) override;

};

#endif
