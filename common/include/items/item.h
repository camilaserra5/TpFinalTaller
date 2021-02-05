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

    Item(){}

    virtual bool obtenerBeneficio(Jugador *jugador) = 0;

    bool estaCerca(int &posx, int &posy) {
        return this->posicion.estaCerca(posx, posy);
    }

    Posicion obtenerPosicion() {
        return this->posicion;
    }

    std::vector<char> serializar() override {
        std::vector<char> informacion;
        std::vector<char> aux(4);
        aux = numberToCharArray(this->id);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        std::vector<char> posicionSerializado = this->posicion.serializar();
        informacion.insert(informacion.end(), posicionSerializado.begin(), posicionSerializado.end());
        return informacion;
    }

    void deserializar(std::vector<char> &serializado) override {
        this->id = (int)serializado[0];
        std::vector<char> posicionSerializado(serializado.begin() + 1,
                                              serializado.end());
        this->posicion.deserializar(posicionSerializado);
    }
    int getId(){
        return this->id;
    }

    virtual Type getTipo() = 0;

    Posicion& getPosicion(){
      return this->posicion;
    }


protected:
    Posicion posicion;
    int id;
};

#endif
