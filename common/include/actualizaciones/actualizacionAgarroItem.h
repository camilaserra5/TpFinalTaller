#ifndef _ACTUALIZACION_AGARRO_ITEM
#define _ACTUALIZACION_AGARRO_ITEM

#include "actualizacion.h"
#include "jugador.h"
#include "items/item.h"

class ActualizacionAgarroItem: public Actualizacion{
public:
    ActualizacionAgarroItem(Jugador* jugador, Item* item): jugador(jugador),
        item(item){}

    ~ActualizacionAgarroItem(){}
    ActualizacionAgarroItem(){}
    std::vector<char> serializar() override{}

    void deserializar(std::vector<char> &serializado) override{}

    int obtenerId() override { return static_cast<int>(Accion::agarreItem); }
private:
        Jugador* jugador;
        Item* item;
};

#endif
