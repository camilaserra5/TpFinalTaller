#include "items/llave.h"

Llave::~Llave(){}

void Llave::obtenerBeneficio(Jugador* jugador){
    jugador->agarrarLlave();
}
