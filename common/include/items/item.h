#ifndef ITEM_H
#define ITEM_H

#include <iserializable.h>
#include "jugador.h"
#include "posicion.h"

class ContenedorDeElementos;

class Item : public ISerializable {
public:
    Item(Posicion &posicion) : posicion(posicion) {}

    virtual ~Item() {}

    virtual void obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) = 0;

    bool estaCerca(int &posx, int &posy) {
        return this->posicion.estaCerca(posx, posy);
    }

    void sacarDelMapa(ContenedorDeElementos &contenedor);

    Posicion obtenerPosicion() {
        return this->posicion;
    }

    std::vector<char> serializar() {
        std::vector<char> informacion;
        informacion.push_back(posicion.pixelesEnX());
        informacion.push_back(posicion.pixelesEnY());
        return informacion;
    }

    void deserializar(std::vector<char>& serializado) {}

protected:
    Posicion posicion;
};

#endif
