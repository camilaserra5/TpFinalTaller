#include "items/balas.h"

#define MAX_BALAS 25


Balas::Balas(Posicion &posicion, int cantidad_balas, int id) : Item(posicion, id), cant_balas(cantidad_balas) {}

Balas::~Balas() {}

bool Balas::obtenerBeneficio(Jugador *jugador) {
    if (jugador->cantidad_balas() != MAX_BALAS) {
        jugador->agregar_balas(this->cant_balas);
        return true;
    }
    return false;
}

Type Balas::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("balas");
}
