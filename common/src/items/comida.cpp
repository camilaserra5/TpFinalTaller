#include "items/comida.h"
#include <iostream>

#define VIDA 10
#define VIDA_MAXIMA 100

Comida::Comida(Posicion &posicion, int id) : Item(posicion, id), puntos_de_vida(VIDA) {}

Comida::~Comida() {}

bool Comida::obtenerBeneficio(Jugador *jugador) {
    std::cout << "obtuve beneficio comida";
    if (jugador->puntos_de_vida() != VIDA_MAXIMA) {
        jugador->actualizar_vida(this->puntos_de_vida);
        return true;
    }
    return false;
}

Type Comida::getTipo(){
    return Type::comida;
}
