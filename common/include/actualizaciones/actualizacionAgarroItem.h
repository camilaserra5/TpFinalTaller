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

class ActualizacionAgarroItem : public Actualizacion {
public:
    /*
      * creara la actualizacion de agarrar item dejandola valida para uso
    */
    ActualizacionAgarroItem(Jugador *jugador, Item *item);
    /*
      * liberara la actualizacion agarrar item con sus recursos
    */
    ~ActualizacionAgarroItem();
    /*
      * constructor por default
    */
    ActualizacionAgarroItem();
    /*
      * serializa la clase y devuelve la serializacion en un vector de caracteres
    */
    std::vector<char> serializar() override;
    /*
      * deserializa el item y lo devuelve creado
    */
    Item *deserializarItem(std::vector<char> &informacion);
    /*
      * deserializa la clase actualizacion agarrar item
    */
    void deserializar(std::vector<char> &serializado) override;
    /*
      * devuelve el jugador que agarro el item
    */
    Jugador *obtenerJugador() {
        return this->jugador;
    }
    /*
      * devuelve el item que agarro el juagdor
    */
    Item *obtenerItem() {
        return this->item;
    }
    /*
      * devuelve el id de la actualizacion
    */  
    int obtenerId() override { return static_cast<int>(Accion::agarreItem); }

private:
    Jugador *jugador;
    Item *item;
};

#endif
