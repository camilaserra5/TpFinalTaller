#ifndef BJETOJUEGO_H
#define OBJETOJUEGO_H

#include "textura.h"
#include "lienzo.h"

//OBJETO JUEGO DIBUJABLE!!!!!!!!!!!!!
class ObjetoJuego {
private:
    int alto;
    int ancho;
    SDL_Renderer *render;
    Textura *textura;

public:
    ObjetoJuego(const char *rutaimg, SDL_Renderer *render, int ancho, int alto);

    ~ObjetoJuego() {}

    void renderizar(int posx, int posy, int angulo);

};

#endif //OBJETOJUEGO_H
