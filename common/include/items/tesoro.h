#ifndef TESORO_H
#define TESORO_H


#include "item.h"

class Tesoro : public Item {
public:
    /*
      * crearar la clase Tesoro dejandola valida para uso
    */
    Tesoro(int id, Type tipo, int puntos, Posicion &posicion);
    /*
      * liberara la clase con sus recursos
    */
    ~Tesoro();
    /*
      * devueltre true si pudo obtener el benefico o false sino
    */
    bool obtenerBeneficio(Jugador *jugador) override;
    /*
      * devuelve el tipo de item
    */  
    Type getTipo() override;

private:
    int puntos;
    Type tipo;
};

#endif
