#ifndef _SPRITE_H
#define _SPRITE_H


#include "textura.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Sprite{
    private:
        Textura* textura;
        SDL_Rect infoSprite;

    public:

        Sprite(SDL_Renderer* render, const char* rutaimg, int x, int y, int h, int w){

            this->infoSprite.x = x;
            this->infoSprite.y = y;
            this->infoSprite.w = w;
            this->infoSprite.h = h;
            this->textura = new Textura(rutaimg,render);

        }
        ~Sprite();
        void renderizar(int x, int y, int angulo){
            SDL_Rect destino;
            destino.x = x;
            destino.y = y;
            destino.h = this->infoSprite.h;
            destino.w = this->infoSprite.w;
            this->textura->renderizar(&this->infoSprite, destino);
        }

};

#endif
