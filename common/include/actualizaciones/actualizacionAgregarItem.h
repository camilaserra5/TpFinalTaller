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

class ActualizacionAgregarItem: public Actualizacion{
    public:
    ActualizacionAgregarItem(Item* item);
    ActualizacionAgregarItem(){}
    ~ActualizacionAgregarItem();
    std::vector<char> serializar() override;
    Item* deserializarItem(std::vector<char>& informacion);

    Item* obtenerItem(){
        return this->item;
    }
    void deserializar(std::vector<char> &serializado) override;

    int obtenerId() override { return static_cast<int>(Accion::agregarItem); }
  private:
    Item* item;
};

#endif
