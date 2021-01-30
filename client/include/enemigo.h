#ifndef _ENEMIGO_H
#define _ENEMIGO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "animacion.h"
#include <map>
#include <string>

class Enemigo{
public:
      Enemigo(SDL_Renderer* render, int idArmaJugador);
      ~Enemigo();
      void actualizar(int posx, int posy);
      void renderizar();
private:
      int idArma;
      int posx;
      int posy;
      int angulo;
      int anguloJugador;
      std::multimap<int, std::pair<std::string, Animacion>> enemigos;
};

#endif
