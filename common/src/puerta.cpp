#include "../include/puerta.h"

#define DISTANCIA_APERTURA 3 //pixeles

void Puerta::abrir(){
  this->abierta = true;
}

void Puerta::cerrar(){
  this->abierta = false;
}

bool Puerta::puedeSerAbierta(Posicion& posicionJugador,bool jugadorTieneLlave){
  double distancia = this->posicion.distanciaA(posicionJugador);
  return (distancia <= DISTANCIA_APERTURA && ((jugadorTieneLlave && this->necesitaLlave) || (!this->necesitaLlave)));
}
