#ifndef _ENEMIGO_H
#define _ENEMIGO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "animacion.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

class Enemigo{
public:
      Enemigo(SDL_Renderer* render, int idArmaJugador);
      ~Enemigo();
      void actualizar(int posx, int posy, int idArma, int anguloEnemigo,
                      int anguloJugador, int vida, bool disparando);
      void renderizar();
      int verificarEstado(int posxViejo, int posyViejo, int posxNuevo, int posyNuevo);
private:
      int idArma;
      int posx;
      int posy;
      int angulo;
      int anguloJugador;
      bool disparando;
      std::multimap<int, std::vector<Animacion>> enemigos;
};

#endif
