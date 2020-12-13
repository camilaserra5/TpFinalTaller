#ifndef TEXTURA_H
#define TEXTURA_H

#include "juego.h"

class Textura {
    SDL_Texture *textura;
    SDL_Renderer * render;
public:
    Textura(const char *archivo, SDL_Renderer *un_render);

    ~Textura() {};

    int renderizar(const Lienzo& src, const Lienzo& dest);
};

#endif //TEXTURA_H
