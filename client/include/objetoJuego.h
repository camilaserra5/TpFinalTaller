#ifndef BJETOJUEGO_H
#define OBJETOJUEGO_H

#include "sprite.h"

class ObjetoJuego {
private:
    int posx;
    int posy;
    int angulo;
    Sprite sprite;

public:
    ObjetoJuego(Sprite&& sprite); //a chequear esa doble referencia, pero es por el stdmove

    ~ObjetoJuego();

    void renderizar();

    void settear_estado(int& posx, int& posy);

};

#endif //OBJETOJUEGO_H
