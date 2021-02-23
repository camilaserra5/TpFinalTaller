#include "items/kitsMedicos.h"

#define VIDA 20
#define VIDA_MAXIMA 100

KitsMedicos::KitsMedicos(Posicion &posicion, int id) : Item(posicion, id), puntos_de_vida(VIDA) {}

KitsMedicos::~KitsMedicos() {}

bool KitsMedicos::obtenerBeneficio(Jugador *jugador) {
    if (jugador->puntos_de_vida() != VIDA_MAXIMA) {
        jugador->actualizar_vida(this->puntos_de_vida);
        return true;
    }
    return false;
}

Type KitsMedicos::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("kitsMedicos");
}
