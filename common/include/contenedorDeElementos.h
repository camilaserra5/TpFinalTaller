
#ifndef CONTENEDOR_DE_ELEMENTOS
#define CONTENEDOR_DE_ELEMENTOS

#include <vector>
#include "items/comida.h"
#include "items/balas.h"
#include "items/sangre.h"
#include "items/kitsMedicos.h"
#include "items/noItem.h"
#include "items/llave.h"
#include "items/tesoro.h"
#include "armas/canionDeCadena.h"
#include "armas/ametralladora.h"
#include "entidadPosicionable.h"
#include <string>

class ContenedorDeElementos {

public:
    ContenedorDeElementos();

    ~ContenedorDeElementos();

    void agregarElemento(EntidadPosicionable *elemento);
    //ElementoPosicionable actualizarElementos();
    //std::vector<ElementoPosicionable> elementoEnPosicion();

private:
    std::vector<EntidadPosicionable *> elementos;
};

#endif
