#ifndef LLAVE_H
#define LLAVE_H


#include "item.h"

class Llave : public Item {
public:
    /*
      * creara la llave dejandola valida para uso
      * la llave abre todas las key doors
    */
    Llave(Posicion &posicion, int id) : Item(posicion, id) {}
    /*
      * liberara la clase con sus recursos
    */
    ~Llave();
    /*
      * devuelve true si pudo obtener el beneficio sino false
    */
    bool obtenerBeneficio(Jugador *jugador) override;
    /*
      * devuelve el tipo de item
    */  
    Type getTipo() override;

};

#endif
