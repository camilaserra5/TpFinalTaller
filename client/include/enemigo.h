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
                      int anguloJugador, int vida, bool disparando, int puntaje);
      void renderizar();
      void verificarEstado(int posxViejo, int posyViejo, int posxNuevo,
                          int posyNuevo, int vida, bool disparando);

      int getPuntaje(){
          return this->puntaje;
      }
      
private:
      int idArma;
      int posx;
      int posy;
      int angulo;
      int anguloJugador;
      int estado;
      int puntaje;
      std::multimap<int, std::vector<Animacion>> enemigos;
};

#endif
