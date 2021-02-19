#ifndef OBJETO_DIBUJABLE_H
#define OBJETO_DIBUJABLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "posicion.h"

class ObjetoDibujable {

private:

    double distanciaParcialAJugador;

public:

    void setDistanciaParcialAJugador(double distancia);

    double getDistanciaParcialAJugador();

    virtual void renderizarColumna(SDL_Rect &dimension, SDL_Rect &dest) = 0;

    virtual Posicion &getPosicion() = 0;

    virtual int obtenerAnchura() = 0;

    virtual ~ObjetoDibujable() {}

};


#endif
