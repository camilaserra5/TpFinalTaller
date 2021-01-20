#ifndef BJETOJUEGO_H
#define OBJETOJUEGO_H

#include "textura.h"
#include "lienzo.h"

//OBJETO JUEGO DIBUJABLE!!!!!!!!!!!!!
class ObjetoJuego {
private:
    int xpos;
    int ypos;
    int alto;
    int ancho;
    SDL_Renderer *render;
    Textura *textura;

public:
    ObjetoJuego(const char *rutaimg, SDL_Renderer *render, int x, int y, int ancho, int alto);

    ~ObjetoJuego() {}

    void renderizar();

    void actualizar(int posx, int posy);
};

#endif //OBJETOJUEGO_H
