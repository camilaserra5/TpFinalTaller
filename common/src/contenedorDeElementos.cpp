#include "../include/contenedorDeElementos.h"
/*
void ContenedorDeElementos::aniadirElemento(ElementoPosicionable &elemento){
  this->elementos.add(elemento);
}
*/

ContenedorDeElementos::ContenedorDeElementos():
    elementos(){}

ContenedorDeElementos::~ContenedorDeElementos(){}

void ContenedorDeElementos::agregarElemento(EntidadPosicionable* entidad){

    this->elementos.push_back(entidad);
}
