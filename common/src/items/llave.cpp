#include "items/llave.h"

Llave::~Llave() {}

void Llave::obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) {
    jugador->agarrarLlave();
}
