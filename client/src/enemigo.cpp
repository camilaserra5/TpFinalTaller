#include "../include/enemigo.h"
#define GUARDIA "../../client/resources/images/Guard.png"
#define RATA "../../client/resources/images/Rat.png"
#define OFFICER "../../client/resources/images/Officer.png"
#define MUTANTE "../../client/resources/images/Mutant.png"
#define ELITE_GUARD "../../client/resources/images/Elite Guard.png"
#define SPRITE_W 74.6
#define SPRITE_H 74
#define FRAMES_X 3
#define FRAMES_Y 4
#define MORIRSE 0
#define MOVERSE 1
#define DISPARAR 2

#define ID_CUCHILLO 3
#define ID_PISTOLA 4
#define ID_AMETRALLADORA 1
#define ID_LANZACOHETES 5
#define ID_CANION_DE_CADENA 2



Enemigo::Enemigo(SDL_Renderer* render, int idArmaJugador):
          idArma(idArmaJugador), posx(0), posy(0),
          angulo(0), anguloJugador(0), estado(MOVERSE){
              // guardia
              Animacion dispararG(render, GUARDIA, FRAMES_Y, SPRITE_H, SPRITE_W, -1,0); // disparar
              Animacion moverseG(render, GUARDIA, FRAMES_Y, SPRITE_H, SPRITE_W, -1,1);
              Animacion morirseG(render, GUARDIA, FRAMES_Y, SPRITE_H, SPRITE_W, -1,2);

              std::vector<Animacion> guardia;
              guardia.push_back(morirseG);
              guardia.push_back(moverseG);
              guardia.push_back(dispararG);

              Animacion dispararR(render, RATA, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 0);
              Animacion moverseR(render, RATA, FRAMES_Y, SPRITE_H, SPRITE_W, -1,1);
              Animacion morirseR(render, RATA, FRAMES_Y, SPRITE_H, SPRITE_W, -1,2);

              std::vector<Animacion> rata;
              rata.push_back(morirseR);
              rata.push_back(moverseR);
              rata.push_back(dispararR);

              Animacion dispararM(render, MUTANTE, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 0);
              Animacion moverseM(render, MUTANTE, FRAMES_Y, SPRITE_H, SPRITE_W, -1,1);
              Animacion morirseM(render, MUTANTE, FRAMES_Y, SPRITE_H, SPRITE_W, -1,2);

              std::vector<Animacion> mutante;
              mutante.push_back(morirseM);
              mutante.push_back(moverseM);
              mutante.push_back(dispararM);

              Animacion dispararO(render, OFFICER, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 0);
              Animacion moverseO(render, OFFICER, FRAMES_Y, SPRITE_H, SPRITE_W, -1,1);
              Animacion morirseO(render, OFFICER, FRAMES_Y, SPRITE_H, SPRITE_W, -1,2);

              std::vector<Animacion> officer;
              officer.push_back(morirseO);
              officer.push_back(moverseO);
              officer.push_back(dispararO);

              Animacion dispararEG(render, ELITE_GUARD, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 0);
              Animacion moverseEG(render, ELITE_GUARD, FRAMES_Y, SPRITE_H, SPRITE_W, -1,1);
              Animacion morirseEG(render, ELITE_GUARD, FRAMES_Y, SPRITE_H, SPRITE_W, -1,2);

              std::vector<Animacion> elite_guard;
              elite_guard.push_back(morirseEG);
              elite_guard.push_back(moverseEG);
              elite_guard.push_back(dispararEG);

              this->enemigos.insert(std::make_pair(ID_PISTOLA, guardia));
              this->enemigos.insert(std::make_pair(ID_CUCHILLO, rata));
              this->enemigos.insert(std::make_pair(ID_LANZACOHETES, mutante));
              this->enemigos.insert(std::make_pair(ID_CANION_DE_CADENA, officer));
              this->enemigos.insert(std::make_pair(ID_AMETRALLADORA, elite_guard));
          }

Enemigo::~Enemigo(){}

void Enemigo::actualizar(int posx, int posy, int idArmaJugador,
                        int anguloEnemigo,int anguloJugador, int vida,
                        bool disparando){
      verificarEstado(this->posx, this->posy, posx,
                                      posy, vida, disparando);
      this->posx = posx;
      this->posy = posy;
      this->idArma = idArmaJugador;
      this->anguloJugador = anguloJugador;
      this->angulo = anguloEnemigo;
}
void Enemigo::verificarEstado(int posxVieja, int posyVieja, int posxNueva,
                                int posyNueva, int vida, bool disparando){
      if (disparando){
          this->estado = DISPARAR;
      } else if (vida <=0){
          this->estado = MORIRSE;
      } else if (posxVieja == posxNueva && posyVieja == posyNueva){
          this->estado = MOVERSE;
      } else {
          this->estado = MOVERSE;
      }
}

void Enemigo::renderizar(){
      std::vector<Animacion>& tipo = this->enemigos.find(this->idArma)->second;
      tipo[this->estado].renderizar(this->posx, this->posy, 0, NULL);

}
