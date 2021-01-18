#include "../include/contenedorDeElementos.h"
<<<<<<< HEAD
=======
#include <iostream>
>>>>>>> main

/*
void ContenedorDeElementos::aniadirElemento(ElementoPosicionable &elemento){
  this->elementos.add(elemento);
}
*/

ContenedorDeElementos::ContenedorDeElementos() :
        elementos() {}
<<<<<<< HEAD

ContenedorDeElementos::~ContenedorDeElementos() {}

void ContenedorDeElementos::agregarElemento(EntidadPosicionable *entidad) {
=======

ContenedorDeElementos::~ContenedorDeElementos() {}
>>>>>>> main

void ContenedorDeElementos::agregarElemento(Item *entidad) {
    std::cout << "agrego elemento\n";
    this->elementos.push_back(entidad);
}

Item *ContenedorDeElementos::buscarElemento(int &posx, int &posy) {
    for (int i = 0; i < this->elementos.size(); i++) {
        if (this->elementos[i]->estaCerca(posx, posy)) {
            return this->elementos[i];
        }
    }
}
