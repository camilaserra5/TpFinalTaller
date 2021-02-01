#include "../include/puerta.h"

#define DISTANCIA_APERTURA 3 //pixeles

void Puerta::abrir(){
  this->abierta = true;
}

void Puerta::cerrar(){
  this->abierta = false;
}

bool Puerta::puedeSerAbierta(bool jugadorTieneLlave,double& distancia)const {
  return (distancia <= DISTANCIA_APERTURA && ((jugadorTieneLlave && this->necesitaLlave) || (!this->necesitaLlave)));
}

double Puerta::distanciaA(Posicion& posicion){
    return this->posicion.distanciaA(posicion);
}
