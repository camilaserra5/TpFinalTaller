
#ifndef CONTENEDOR_DE_ELEMENTOS
#define CONTENEDOR_DE_ELEMENTOS

#include <vector>
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
#include <string>

class ContenedorDeElementos {

public:
    ContenedorDeElementos();

    ~ContenedorDeElementos();

    void agregarElemento(Item *elemento);

    void sacarElementoDePosicion(Posicion &posicion);

    //ElementoPosicionable actualizarElementos();
    //std::vector<ElementoPosicionable> elementoEnPosicion();
    Item *buscarElemento(int &pox, int &posy);

private:
    std::vector<Item *> elementos;
};

#endif
