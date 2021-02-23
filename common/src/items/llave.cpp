#include "items/llave.h"

Llave::~Llave() {}

bool Llave::obtenerBeneficio(Jugador *jugador) {
    jugador->agarrarLlave();
    return true;
}

Type Llave::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("llave");
}
