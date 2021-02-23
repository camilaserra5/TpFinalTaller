
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
    /*
      * crearar el contendor de elemenots dejandolo valido para uso
    */
    ContenedorDeElementos(ConfiguracionPartida& configuracion);
    /*
      * consrrcuotr por default
    */
    ContenedorDeElementos();
    /*
      * liberara el contendor con susu recursos
    */
    ~ContenedorDeElementos();
    /*
      * agregara un item al contendor
    */
    void agregarElemento(Item *elemento);
    /*
      * saca el item que le llega del contenedor
    */
    void sacarElementoDePosicion(Posicion &posicion);
    /*
      * busca el elemento en base a su posicion
    */
    Item *buscarElemento(int &pox, int &posy);
    /*
      * serializa la clase, devoliendo la informacion de ella
    */
    std::vector<char> serializar() override;
    /*
      * deserializa la clase , creandola y dejandola en sus valores
      * correspondientes
    */
    void deserializar(std::vector<char> &serializado) override;
    /*
      * devuleve el vector de items
    */
    std::vector<Item *> &obtenerItems();
    /*
      * devuelve si hay pruertas
    */
    bool hayPuertas();
    /*
      * devuelve la puerta mas cercana
    */
    Puerta &puertaMasCercana(Posicion &posicionJugador, double &distancia);
    /*
      * devuelve la puerta en la fila y columna que llega por parametros
    */
    Puerta *obtenerPuertaEn(int &fila, int &columna);
    /*
      * agregar una puerta al contenedor
    */
    void aniadirPuerta(Puerta &puerta);
    /*
      * constructor por movimiento
      */
    ContenedorDeElementos(ContenedorDeElementos&& contenedor);
    /*
      * deserializa al item, creandolo y devolviendolo
    */  
    Item *deserializarItem(std::vector<char> &informacion);

private:
    std::vector<Item *> elementos;
    ConfiguracionPartida configuracion;
    std::vector<Puerta> puertas;
};

#endif
