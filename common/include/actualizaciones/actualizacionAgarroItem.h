#ifndef _ACTUALIZACION_AGARRO_ITEM
#define _ACTUALIZACION_AGARRO_ITEM

#include "actualizacion.h"
#include "jugador.h"
#include "items/item.h"
#include "items/comida.h"
#include "items/balas.h"
#include "items/sangre.h"
#include "items/kitsMedicos.h"
#include "items/noItem.h"
#include "items/llave.h"
#include "items/tesoro.h"
#include "armas/canionDeCadena.h"
#include "armas/ametralladora.h"

class ActualizacionAgarroItem: public Actualizacion{
public:
    ActualizacionAgarroItem(Jugador* jugador, Item* item);

    ~ActualizacionAgarroItem();
    ActualizacionAgarroItem();
    std::vector<char> serializar() override;
    Item* deserializarItem(std::vector<char>& informacion);
    void deserializar(std::vector<char> &serializado) override;

    Jugador* obtenerJugador(){
        return this->jugador;
    }
    Item* obtenerItem(){
        return this->item;
    }

    int obtenerId() override { return static_cast<int>(Accion::agarreItem); }
private:
        Jugador* jugador;
        Item* item;
};

#endif
