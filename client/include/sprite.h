#ifndef _SPRITE_H
#define _SPRITE_H


#include "textura.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite {
private:
    Textura *textura;
    SDL_Rect infoSprite;
    SDL_Rect destino;

public:

    Sprite(SDL_Renderer *render, const char *rutaimg, int x, int y, int h, int w);

    ~Sprite() {}

    void renderizar(int x, int y, int angulo);

    void reescalar(int escalarw, int escalarh);

};

#endif