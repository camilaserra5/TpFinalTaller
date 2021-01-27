#include "../include/sprite.h"
#include "../include/textura.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Sprite::Sprite(SDL_Renderer* render, const char* rutaimg, int x, int y, int h, int w){
        this->infoSprite.x = x* w;
        this->infoSprite.y = y* h;
        this->infoSprite.w = w;
        this->infoSprite.h = h;
        this->textura = new Textura(rutaimg,render);
}

void Sprite::renderizar(int x, int y, int angulo){
        SDL_Rect destino;
        destino.x = x;
        destino.y = y;
        destino.h = this->infoSprite.h;
        destino.w = this->infoSprite.w;
        this->textura->renderizar(&this->infoSprite, destino);
}
