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
#include "objetoDibujable.h"

class Enemigo: public ObjetoDibujable{
public:
      Enemigo(SDL_Renderer* render, int idArmaJugador);
      ~Enemigo();
      void actualizar(int posx, int posy, int idArma, int anguloEnemigo,
                      int anguloJugador, int vida, bool disparando, int puntaje);
      void renderizar();

      void verificarEstado(Posicion& posicionNueva,int vida, bool disparando);

      void renderizarColumna(SDL_Rect& dimension,SDL_Rect& dest) override;

      Posicion& getPosicion();

      int getPuntaje(){
          return this->puntaje;

      int obtenerAnchura();

private:
      int idArma;
      int anguloJugador;
      int estado;
      int distanciaParcialAJugador;
      Posicion posicion;
      std::multimap<int, std::vector<Animacion>> enemigos;
      int puntaje;
};

#endif
