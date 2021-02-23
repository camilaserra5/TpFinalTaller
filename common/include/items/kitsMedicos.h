#ifndef KITS_MEDICOS_H
#define KITS_MEDICOS_H

#include "item.h"

class KitsMedicos : public Item {
public:
    /*
      * crearar la clase kitsMedicos dejandola valida para uso
    */
    KitsMedicos(Posicion &posicion, int id,int vidaMaxJugador, int vidaKits);
    /*
      * liberara la clase con sus recursos
    */
    ~KitsMedicos();
    /*
      * devuelve true si pudo obtener el beneifico sino no
    */
    bool obtenerBeneficio(Jugador *jugador) override;
    /*
      * devuelve el tipo
    */
    Type getTipo() override;


private:
    int puntos_de_vida;
    int maxPuntosDeVida;
};

#endif
