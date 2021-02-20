#ifndef ITEM_H
#define ITEM_H

#include <iserializable.h>
#include "jugador.h"
#include "posicion.h"
#include "objetosJuego.h"

class ContenedorDeElementos;

class Item : public ISerializable {
public:
    Item(Posicion &posicion, int id);

    virtual ~Item() {}

    Item();

    virtual bool obtenerBeneficio(Jugador *jugador) = 0;

    bool estaCerca(int &posx, int &posy);

    Posicion obtenerPosicion();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    int getId();

    virtual Type getTipo() = 0;

    Posicion &getPosicion();


protected:
    Posicion posicion;
    int id;
};

#endif
