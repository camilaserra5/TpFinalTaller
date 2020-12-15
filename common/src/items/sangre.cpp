#include "items/sangre.h"

#define VIDA 1
#define VIDA_MAXIMA 11

Sangre::Sangre(Posicion &posicion):Item(posicion),puntos_de_vida(VIDA) {}

Sangre::~Sangre() {}

void Sangre::obtenerBeneficio(Jugador *jugador) {
    if (jugador->puntos_de_vida() <= VIDA_MAXIMA) {
        jugador->actualizar_vida(this->puntos_de_vida);
    }
}
