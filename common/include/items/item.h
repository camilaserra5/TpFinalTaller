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

    std::vector<char> serializar() override; /* {
        std::vector<char> informacion;
        std::vector<char> aux(4);
        aux = numberToCharArray(this->id);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        std::vector<char> posicionSerializado = this->posicion.serializar();
        informacion.insert(informacion.end(), posicionSerializado.begin(), posicionSerializado.end());
        return informacion;
    }*/

    void deserializar(std::vector<char> &serializado) override; /* {
        std::vector<char> sub(4);
        int idx = 0;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->id = charArrayToNumber(sub);
        idx += 4;
        std::vector<char> posicionSerializado(serializado.begin() + idx, serializado.end());
        this->posicion.deserializar(posicionSerializado);
    }*/

    int getId();

    virtual Type getTipo() = 0;

    Posicion &getPosicion();


protected:
    Posicion posicion;
    int id;
};

#endif
