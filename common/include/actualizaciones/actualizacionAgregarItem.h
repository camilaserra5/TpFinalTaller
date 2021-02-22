#ifndef _ACTUALIZACION_AGREGAR_ITEM_
#define _ACTUALIZACION_AGREGAR_ITEM_

#include "actualizacion.h"
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

class ActualizacionAgregarItem : public Actualizacion {
public:
    /*
      * creara la clase actualizacion agregar item y la deja valida para uso
    */
    ActualizacionAgregarItem(Item *item);

    /*
      * contructor por default
    */
    ActualizacionAgregarItem() {}

    /*
      * liberara la clase agarro item con sus recursos
    */
    ~ActualizacionAgregarItem();

    /*
      * serializa la clase y devuelve la informacion
    */
    std::vector<char> serializar() override;

    /*
      * deserializa el item, lo crea y lo devuelve
    */
    Item *deserializarItem(std::vector<char> &informacion);

    /*
      * devuelve el item que se va a agregar
    */
    Item *obtenerItem() {
        return this->item;
    }

    /*
      * deserializa la clase dejandola en sus valores correspondientes
    */
    void deserializar(std::vector<char> &serializado) override;

    /*
      * devuelve el id de la clase
    */
    int obtenerId() override { return static_cast<int>(Accion::agregarItem); }

private:
    Item *item;
};

#endif
