#ifndef OBJETO_DIBUJABLE_H
#define OBJETO_DIBUJABLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "posicion.h"

class ObjetoDibujable {

private:

    double distanciaParcialAJugador;

public:
    /*
      * settea la distancia parcial al juagdor
    */
    void setDistanciaParcialAJugador(double distancia);

    /*
      * devuelve la distancia parcial al juagdor
    */
    double getDistanciaParcialAJugador();

    /*
      * renderiza el obejo por columna
    */
    virtual void renderizarColumna(SDL_Rect &dimension, SDL_Rect &dest) = 0;

    /*
      * devuelve la posicion del obejto
    */
    virtual Posicion &getPosicion() = 0;

    /*
      * devuelve el ancho del sprite
    */
    virtual int obtenerAnchura() = 0;

    /*
      * liberara el objeto dibujable con sus recursos
    */
    virtual ~ObjetoDibujable() {}

};


#endif
