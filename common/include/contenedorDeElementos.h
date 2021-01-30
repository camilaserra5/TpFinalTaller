
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
#include "iserializable.h"
#include <string>

class ContenedorDeElementos : public ISerializable {

public:
    ContenedorDeElementos();

    ~ContenedorDeElementos();

    void agregarElemento(Item *elemento);

    void sacarElementoDePosicion(Posicion &posicion);

    Item *buscarElemento(int &pox, int &posy);

    std::vector<char> serializar() {
        std::vector<char> informacion;
        informacion.push_back(elementos.size());
        for (std::vector<Item *>::iterator it = elementos.begin(); it != elementos.end(); ++it) {
            std::vector<char> itemSerializado = ((Item *) *it)->serializar();
            informacion.insert(informacion.end(), itemSerializado.begin(), itemSerializado.end());
        }
        return informacion;
    }

    void deserializar(std::vector<char>& serializado) {}

private:
    std::vector<Item *> elementos;
};

#endif
