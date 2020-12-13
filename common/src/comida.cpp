#include "../include/comida.h"

#define VIDA 10
#define VIDA_MAXIMA 100

Comida::Comida() {
    this->puntos_de_vida = VIDA;
}

Comida::~Comida() {}

void Comida::obtenerBeneficio(Jugador &jugador) {
    if (jugador.puntos_de_vida() != VIDA_MAXIMA) {
        jugador.actualizar_vida(this->puntos_de_vida);
    }
}
