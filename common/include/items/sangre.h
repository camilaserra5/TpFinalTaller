#ifndef SANGRE_H
#define SANGRE_H

#include "item.h"

class Sangre : public Item {
public:
    /*
      * creara la clase sangre dejandola valida para uso
    */
    Sangre(Posicion &posicion, int id);
    /*
      * liberarar la clase con sus recursos
    */
    ~Sangre();
    /*
      * devuelve true si pudo obtener el benefico o false si no
    */
    bool obtenerBeneficio(Jugador *jugador) override;
    /*
      * devuelve el tipo de item
    */  
    Type getTipo() override;

private:
    int puntos_de_vida;
};

#endif
