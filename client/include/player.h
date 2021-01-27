#ifndef _PLAYER_H
#define _PLAYER_H

// no se si es un sprite;
// falta ver tema imagen/arma
#include "sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

class Player{
    public:
        Player(const char* rutaimg, SDL_Renderer* render, int id);

        ~Player();
        // actualizacion
        void settear_estado(int posx, int posy, int vida, int angulo);
        void renderizar();

    private:
      int posx;
      int posy;
      int vida;
      int angulo;
      int id;
      std::map<std::string, Sprite> sprites;
};

#endif
