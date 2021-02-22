#ifndef BALAS_H
#define BALAS_H

#define BALAS 5

#include "item.h"

class Balas : public Item {
public:
    /*
      * creara la clase balas dejandla valida para uso
    */
    Balas(Posicion &posicion, int cantidad, int id);
    /*
      * liberara la clase con sus recursos
    */
    ~Balas();
    /*
      * devulve tru si pudo agarrar las balas o false sino
    */
    bool obtenerBeneficio(Jugador *jugador) override;
    /*
      * devuelve el tipo
    */  
    Type getTipo() override;

private:
    int cant_balas;
};

#endif
