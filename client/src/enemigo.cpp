#include "../include/enemigo.h"
#define GUARDIA "../../client/resources/images/Guard.png"
#define SPRITE_W 74.6
#define SPRITE_H 74
#define FRAMES_X 3
#define FRAMES_Y 4
#define MORIRSE 0
#define MOVERSE 1
#define DISPARAR 2

Enemigo::Enemigo(SDL_Renderer* render, int idArmaJugador):
          idArma(idArmaJugador), posx(0), posy(0),
          angulo(0), anguloJugador(0){
              // guardia
              Animacion dispararG(render, GUARDIA, FRAMES_Y, SPRITE_H, SPRITE_W, -1,0); // disparar
              Animacion moverseG(render, GUARDIA, FRAMES_Y, SPRITE_H, SPRITE_W, -1,1);
              Animacion morirseG(render, GUARDIA, FRAMES_Y, SPRITE_H, SPRITE_W, -1,2);

              std::vector<Animacion> guardia;
              guardia.push_back(morirseG);
              guardia.push_back(moverseG);
              guardia.push_back(dispararG);

              this->enemigos.insert(std::make_pair(idArmaJugador, guardia));
          }

Enemigo::~Enemigo(){}

void Enemigo::actualizar(int posx, int posy, int idArmaJugador, int anguloEnemigo,  int anguloJugador, int vida){
      this->angulo = verificarEstado(this->posx, this->posy, posx, posy);
      this->posx = posx;
      this->posy = posy;
      this->idArma = idArmaJugador;
      this->anguloJugador = anguloJugador;
      this->angulo = anguloEnemigo;
}
  int Enemigo::verificarEstado(int posxVieja, int posyVieja, int posxNueva, int posyNueva){
      if (posxVieja == posxNueva && posyVieja == posyNueva){
          // no me movi;
                return this->angulo = 0;

      } else if (posxVieja > posxNueva){
                // me movi izquierda;
                return this->angulo = -90;

      } else if (posxVieja < posxNueva){
              // me movi a derecha;
                return this->angulo = 90;
      } else if (posyVieja > posyNueva){
              return this->angulo = 0;
          // me movi abajo
      } else if (posyVieja < posyNueva){
          // me movi a arriba
            return this->angulo = 0;
      }
  }

void Enemigo::renderizar(){
      std::vector<Animacion> tipo = this->enemigos.find(this->idArma)->second;
      SDL_Point point;
      point.x = this->posx + SPRITE_W/2;
      point.y = this->posy + SPRITE_H/2;
      tipo[MOVERSE].renderizar(this->posx, this->posy, 0, &point);

}
