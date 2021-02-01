#include "items/balas.h"

#define MAX_BALAS 25


Balas::Balas(Posicion &posicion, int cantidad_balas, int id) : Item(posicion, id), cant_balas(cantidad_balas) {}

Balas::~Balas() {}

void Balas::obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) {
    if (jugador->cantidad_balas() != MAX_BALAS) {
        jugador->agregar_balas(this->cant_balas);
        //sacar del mapa
    }
}
Type Balas::getTipo(){
    return Type::balas;
}
