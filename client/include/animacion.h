#ifndef _ANIMACION_H
#define _ANIMACION_H

//nframes = SDL_GetTicks()/velocidad % cantFrames

#include "textura.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Animacion{
    public:
        Animacion();
        ~Animacion();
        void render(int posx, int posy, int anchoSprite, int largoSprite){

            SDL_Rect srcRect = {anchoSprite*spriteContador, largoSprite*row, anchoSprite, largoSprite};
            SDL_Rect srcDest = {posx, posy, anchoSprite, largoSprite};
            this->textura.renderizar(&srcRect, srcDest);

        }
        void setPropiedades(SDL_Render* render, const char* rutaimg, int cantframes, int spritefila, int velocidad){
            Textura* textura = new Textura(rutaimg, render);
            this->spriteContador = 0;
            this->spriteFila = spritefila;
            this->velocidad = velocidad;
            this->cantframes = nframes;
        }

        void actualizar(){
            this->spriteContador = SDL_GetTicks()/this->velocidad % this->cantFrames;
        }

    private:
          Textura* textura;
          int cantframes;
          int spriteFila;
          int spriteContador;
          int velocidad;
};

#endif
