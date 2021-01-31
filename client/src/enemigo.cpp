#include "../include/enemigo.h"
#define GUARDIA "../include/client/resources/Guard.png"
#define SPRITE_W 65
#define SPRITE_H 64
#define FRAMES_X 3
#define FRAMES_Y 4
#define MORIRSE 15
/*
Enemigo::Enemigo(SDL_Renderer* render, int idArmaJugador):
          idArma(idArmaJugador), posx(0), posy(0),
          angulo(0), anguloJugador(0){
              // guardia
              Animacion dispararG(render, GUARDIA, FRAMES_Y, SPRITE_H, SPRITE_W, 0); // disparar
              Animacion moverseG(render, GUARDIA, FRAMES_Y, SPRITE_H, SPRITE_W, 1);
              Animacion morirseG(render, GUARDIA, FRAMES_Y, SPRITE_H, SPRITE_W, 2);
              std::pair<std::string, Animacion> guardia;
              guardia.first = "moverse";
              guardia.
              guardia.insert(std::make_pair<"moverse", moverseG);
              guardia.insert(std::make_pair<"morirse", morirseG);
              this->enemigos.insert(std::make_pair<idArmaJugador, guardia);
          }

Enemigo::~Enemigo(){}

void Enemigo::actualizar(int posx, int posy, ind idArmaJugador, int anguloJugador){
      this->angulo = verificarEstado(this->posx, this->posy, posx, posy)
      this->posx = posx;
      this->posy = posy;
      this->idArma = idArmaJugador;
      this->anguloJugador = anguloJugador;
}
  int verificarEstado(int posxVieja, int posyVieja, int posxNueva, int posyNueva){
      if (posxVieja == posxNuevo && posyVieja == posyNueva){
          // no me movi;
                return this->angulo = 0;

      } else if (posxVieja > posxNueva){
                // me movi izquierda;
                return this->angulo = -90;

      } else if (posxVieja < posxNueva){
              // me movi a derecha;
                return this->angulo = 90
      } else if (posyVieja > posyNueva){
              return this->angulo = 0;
          // me movi abajo
      } else if (posyVieja < posyNueva){
          // me movi a arriba
            return this->angulo = 0;
      }
  }

void Enemigo::renderizar(){
      std::map<std::string, Animacion> tipo = this->enemigos.at(this->idArma);
      tipo.at("moverse").renderizar(this->posx, this->posy, this->angulo);

}*/
