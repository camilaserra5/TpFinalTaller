#include "items/tesoro.h"


Tesoro::Tesoro(int id, Type tipo, int puntos, Posicion &posicion) :
        Item(posicion, id),
        puntos(puntos),
        tipo(tipo) {}

Tesoro::~Tesoro() {}

bool Tesoro::obtenerBeneficio(Jugador *jugador) {
    jugador->sumarPuntos(this->puntos);
    return true;
}

Type Tesoro::getTipo() {
    return this->tipo;
}
