#ifndef ITEM_H
#define ITEM_H

#include <iserializable.h>
#include "jugador.h"
#include "posicion.h"
#include "objetosJuego.h"

class ContenedorDeElementos;

class Item : public ISerializable {
public:
    /*
      * creara la clase item dejandola valido para uso
    */
    Item(Posicion &posicion, int id);
    /*
      * destruira la clase con sus recursos
    */
    virtual ~Item() {}
    /*
      * constrcutor por default
    */
    Item();
    /*
      * devolvera true si pudo obtener el beneficion o false si no
    */
    virtual bool obtenerBeneficio(Jugador *jugador) = 0;
    /*
      * devuelve true si el item esta cerca de la poscion que le llega
    */
    bool estaCerca(int &posx, int &posy);
    /*
      * devuelve su posicion
    */
    Posicion obtenerPosicion();
    /*
      * serializa la clase devolviendo su informacion
    */
    std::vector<char> serializar() override;
    /*
      * deserializa la clase creandola y dejandola en sus valores
      * correspondientes
    */
    void deserializar(std::vector<char> &serializado) override;
    /*
      * devuleve el id
    */
    int getId();
    /*
      * devuelve el tipo de item
    */
    virtual Type getTipo() = 0;
    /*
      * devuleve la poscion
    */  
    Posicion &getPosicion();


protected:
    Posicion posicion;
    int id;
};

#endif
