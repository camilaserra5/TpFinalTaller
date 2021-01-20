#ifndef ITEM_H
#define ITEM_H

#include "jugador.h"
#include "posicion.h"

class ContenedorDeElementos;

class Item{
public:
    Item(Posicion &posicion) : posicion(posicion) {}

    virtual ~Item() {}

    virtual void obtenerBeneficio(ContenedorDeElementos &contenedor,Jugador *jugador) = 0;

    bool estaCerca(int &posx, int &posy) {
        return this->posicion.estaCerca(posx, posy);
    }

    void sacarDelMapa(ContenedorDeElementos &contenedor, Posicion &posicion);


private:
    Posicion posicion;
};

#endif
