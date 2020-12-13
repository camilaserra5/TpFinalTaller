#ifndef TEXTURA_H
#define TEXTURA_H

#include "juego.h"

class Textura {
    SDL_Texture *textura;
public:
    Textura(const char *archivo, SDL_Renderer *un_render);

    ~Textura() {};

    SDL_Texture *cargarTextura();
};

#endif //TEXTURA_H
