#include "../include/contenedorDeElementos.h"
#include <iostream>

Puerta& ContenedorDeElementos::puertaMasCercana(Posicion& posicionJugador,double& distancia){
  int cantPuertas = this->puertas.size();
  int posPuertaMasCercana = 0;
  distancia = this->puertas[0].distanciaA(posicionJugador);
    for (int i = 1; i < cantPuertas; i++){
      double distanciaParcial = this->puertas[i].distanciaA(posicionJugador);
      if (distanciaParcial < distancia){
          distancia = distanciaParcial;
          posPuertaMasCercana = i;
      }
    }
    return this->puertas[posPuertaMasCercana];
}

void ContenedorDeElementos::agregarElemento(Item *item) {
    this->elementos.push_back(item);
}

void ContenedorDeElementos::sacarElementoDePosicion(Posicion &posicion) {
    std::vector<Item *> elementosFiltrados;
    for (int i = 0; i < this->elementos.size(); i++) {
        if (this->elementos[i]->obtenerPosicion() == posicion) {
            delete this->elementos[i];
        } else {
            elementosFiltrados.push_back(this->elementos[i]);
        }
    }
    this->elementos.swap(elementosFiltrados);
}

ContenedorDeElementos::ContenedorDeElementos() :
        elementos() {}

ContenedorDeElementos::~ContenedorDeElementos() {}

Item *ContenedorDeElementos::buscarElemento(int &posx, int &posy) {
    for (int i = 0; i < this->elementos.size(); i++) {
        if (this->elementos[i]->estaCerca(posx, posy)) {
            return this->elementos[i];
        }
    }
    return nullptr;
}

bool ContenedorDeElementos::hayPuertas(){
  return (this->puertas.size() > 0);
}
// serializar items 3 enteros;
// pos x, posy, id;
//primero mandar la longutid de la cantidad de items y luego los items;
