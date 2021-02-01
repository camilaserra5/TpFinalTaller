#ifndef ITEM_H
#define ITEM_H

#include <iserializable.h>
#include "jugador.h"
#include "posicion.h"
#include "objetosJuego.h"

class ContenedorDeElementos;

class Item : public ISerializable {
public:
    Item(Posicion &posicion, int id) : posicion(posicion), id(id) {}

    virtual ~Item() {}

    virtual void obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) = 0;

    bool estaCerca(int &posx, int &posy) {
        return this->posicion.estaCerca(posx, posy);
    }

    void sacarDelMapa(ContenedorDeElementos &contenedor);

    Posicion obtenerPosicion() {
        return this->posicion;
    }

    std::vector<char> serializar() override {
        return this->posicion.serializar();
    }

    void deserializar(std::vector<char> &serializado) override {
        this->posicion.deserializar(serializado);
    }
    int getId(){
        return this->id;
    }

    virtual Type getTipo() = 0;


protected:
    Posicion posicion;
    int id;
};

#endif
