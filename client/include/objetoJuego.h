#ifndef BJETOJUEGO_H
#define OBJETOJUEGO_H

#include "sprite.h"
#include "posicion.h"

class ObjetoJuego {
private:
    Posicion posicion;
    Sprite sprite;
    int distanciaParcialAJugador;

public:
    ObjetoJuego(Sprite sprite); //a chequear esa doble referencia, pero es por el stdmove

    ~ObjetoJuego();

    void renderizar();

    void settear_estado(int posx, int posy);

    void setDistanciaParcialAJugador(int& distancia);

    int getDistanciaParcialAJugador();

    Posicion& getPosicion();

    void renderizarColumna(SDL_Rect& dimension,SDL_Rect& dest);

    void reescalar(int escalarw, int escalarh);
};

#endif //OBJETOJUEGO_H
