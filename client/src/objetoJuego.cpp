#include "../include/objetoJuego.h"

ObjetoJuego::ObjetoJuego(Sprite&& sprite) :
        sprite(sprite),
        posicion(0,0,0){}

ObjetoJuego::~ObjetoJuego() {}

void ObjetoJuego::renderizar() {
    this->sprite.renderizar(this->posicion.pixelesEnX(), this->posicion.pixelesEnY(), this->angulo, NULL);
}

void ObjetoJuego::settear_estado(int& posx, int& posy) {
  this->posicion.actualizarPosicion(posx,posy);
}

void ObjetoJuego::setDistanciaParcialAJugador(int& distancia){
    this->distanciaParcialAJugador = distancia;
}

int ObjetoJuego::getDistanciaParcialAJugador(){
  return this->distanciaParcialAJugador;
}

Posicion& ObjetoJuego::getPosicion(){
    return this->posicion;
}
