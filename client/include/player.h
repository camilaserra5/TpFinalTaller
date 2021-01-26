#ifndef _PLAYER_H
#define _PLAYER_H

// no se si es un sprite;
// falta ver tema imagen/arma
#include "sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Player{
    public:
        Player(const char* rutaimg, SDL_Renderer* render, int id):
        posx(0),
        posy(0),
        vida(100),
        angulo(50),
        id(id),                 
        sprite(render, rutaimg, 3, 3, 65, 60){}

        ~Player();
        // actualizacion
        void settear_estado(int posx, int posy, int vida, int angulo){
            this->posx = posx;
            this->posy = posy;
            this->vida = vida;
            this->angulo = angulo;
        }
        void renderizar(){
            this->sprite.renderizar(this->posx, this->posy, this->angulo);
        }
    private:
      int posx;
      int posy;
      int vida;
      int angulo;
      int id;
      Sprite sprite;
};

#endif
