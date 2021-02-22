
#ifndef CONTENEDOR_DE_ELEMENTOS
#define CONTENEDOR_DE_ELEMENTOS

#include <vector>
#include "puerta.h"
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
    ContenedorDeElementos(ConfiguracionPartida& configuracion);

    ContenedorDeElementos();

    ~ContenedorDeElementos();

    void agregarElemento(Item *elemento);

    void sacarElementoDePosicion(Posicion &posicion);

    Item *buscarElemento(int &pox, int &posy);

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    std::vector<Item *> &obtenerItems();

    bool hayPuertas();

    Puerta &puertaMasCercana(Posicion &posicionJugador, double &distancia);

    Puerta &obtenerPuertaEn(int &fila, int &columna);

    void aniadirPuerta(Puerta &puerta);

    Item *deserializarItem(std::vector<char> &informacion);

private:
    std::vector<Item *> elementos;
    ConfiguracionPartida configuracion;
    std::vector<Puerta> puertas;
};

#endif
