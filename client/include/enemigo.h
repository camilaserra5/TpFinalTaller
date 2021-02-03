#ifndef _ENEMIGO_H
#define _ENEMIGO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "animacion.h"
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "posicion.h"

class Enemigo{
public:
      Enemigo(SDL_Renderer* render, int idArmaJugador);
      ~Enemigo();
      void actualizar(int posx, int posy, int idArma, int anguloEnemigo,
                      int anguloJugador, int vida, bool disparando);
      void renderizar();
      void verificarEstado(Posicion& posicionNueva,int vida, bool disparando);

      int getDistanciaParcialAJugador();

      void setDistanciaParcialAJugador(int distancia);

      Posicion& getPosicion();

private:
      int idArma;
      int anguloJugador;
      int estado;
      int distanciaParcialAJugador;
      Posicion posicion;
      std::multimap<int, std::vector<Animacion>> enemigos;
};

#endif
