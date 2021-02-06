#include "../include/puerta.h"

#define DISTANCIA_APERTURA 3 //pixeles

void Puerta::abrir() {
    this->abierta = true;
}

void Puerta::cerrar() {
    this->abierta = false;
}

bool Puerta::puedeSerAbierta(bool jugadorTieneLlave, double &distancia) const {
    return (distancia <= DISTANCIA_APERTURA && ((jugadorTieneLlave && this->necesitaLlave) || (!this->necesitaLlave)));
}

double Puerta::distanciaA(Posicion &posicion) {
    return this->posicion.distanciaA(posicion);
}

bool Puerta::estaAbierta() {
    return this->abierta;
}

bool Puerta::estaEnPosDelMapa(int &fila, int &columna) {
    return (this->fila == fila && this->columna == columna);
}
