#ifndef COMIDA_H
#define COMIDA_H

#include "item.h"

class Comida : public Item {
public:
    /*
      * crearar la clase comida dejandola valida para uso
    */
    Comida(Posicion &posicion, int id, int puntosVidaComida,int vidaMaxJugador);
    /*
      * liberara la comida con sus recursos
    */
    ~Comida();
    /*
      * devuelve true si pudo agarrar la comida o false sino
    */
    bool obtenerBeneficio(Jugador *jugador) override;
    /*
      * devuelve el tipo
    */
    Type getTipo() override;

private:
    int puntos_de_vida;
    int puntosDeVidaMax;
};

#endif
