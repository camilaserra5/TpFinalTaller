#include "../include/puerta.h"

#define DISTANCIA_APERTURA  23 //pixeles,en realidad es ladocelda/2 + error

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

std::vector<char> Puerta::serializar(){
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->fila);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(this->columna);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(this->abierta);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    std::vector<char> posicionSerializado = this->posicion.serializar();
    informacion.insert(informacion.end(), posicionSerializado.begin(),
                       posicionSerializado.end());
    return informacion;
}
