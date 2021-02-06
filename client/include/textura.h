#ifndef TEXTURA_H
#define TEXTURA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Textura {
    SDL_Texture *textura;
    SDL_Renderer *render;
public:
    Textura(const char *archivo, SDL_Renderer *un_render);

    ~Textura() {}

    int renderizar(SDL_Rect *infoSprite, SDL_Rect destino, int angulo, SDL_Point *centro) const;
};

#endif //TEXTURA_H
