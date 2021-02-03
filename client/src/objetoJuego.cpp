#include "../include/objetoJuego.h"

ObjetoJuego::ObjetoJuego(Sprite sprite) :
        sprite(sprite),
        posicion(0,0,0){}

ObjetoJuego::~ObjetoJuego() {}

void ObjetoJuego::renderizar() {
    this->sprite.renderizar(this->posicion.pixelesEnX(), this->posicion.pixelesEnY(), this->posicion.getAnguloDeVista(), NULL);
}

void ObjetoJuego::settear_estado(int posx, int posy) {
  this->posicion.actualizar_posicion(posx,posy);
}

void ObjetoJuego::setDistanciaParcialAJugador(double& distancia){
    this->distanciaParcialAJugador = distancia;
}

int ObjetoJuego::getDistanciaParcialAJugador(){
  return this->distanciaParcialAJugador;
}

Posicion& ObjetoJuego::getPosicion(){
    return this->posicion;
}

void ObjetoJuego::renderizarColumna(SDL_Rect& dimension,SDL_Rect& dest){
  this->sprite.renderizarColumna(dimension,dest);
}

void ObjetoJuego::reescalar(int escalarw, int escalarh){
    this->sprite.reescalar(escalarw, escalarh);
}
