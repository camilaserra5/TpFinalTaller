#include "items/llave.h"

Llave::~Llave() {}

bool Llave::obtenerBeneficio(Jugador *jugador) {
    jugador->agarrarLlave();
    return true;//lo dejamos asi asi el jugador le saca las llaves a los demas
}

Type Llave::getTipo(){
    return  ObjetosJuego::obtenerTipoPorNombre("llave");
}
