#include "../include/contenedorDeElementos.h"
#include <iostream>
/*
void ContenedorDeElementos::aniadirElemento(ElementoPosicionable &elemento){
  this->elementos.add(elemento);
}
*/

ContenedorDeElementos::ContenedorDeElementos():
    elementos(){}

ContenedorDeElementos::~ContenedorDeElementos(){}

void ContenedorDeElementos::agregarElemento(Item* entidad){
    std::cout << "agrego elemento\n";
    this->elementos.push_back(entidad);
}

Item* ContenedorDeElementos::buscarElemento(int& posx, int& posy){
    for (int i = 0; i< this->elementos.size(); i++){
          if (this->elementos[i]->estaCerca(posx, posy)){
                return this->elementos[i];
          }
    }
}
