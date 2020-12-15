#include "items/llave.h"


Llave::Llave(){}

Llave::~Llave(){}

void Llave::obtenerBeneficio(Jugador* jugador){
    jugador->agarrarLlave();
}
