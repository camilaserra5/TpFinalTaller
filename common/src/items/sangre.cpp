#include "items/sangre.h"

#define VIDA 1
#define VIDA_MAXIMA 11

Sangre::Sangre(Posicion &posicion, int id) : Item(posicion, id), puntos_de_vida(VIDA) {}

Sangre::~Sangre() {}

bool Sangre::obtenerBeneficio(Jugador *jugador) {
    if (jugador->puntos_de_vida() <= VIDA_MAXIMA) {
        jugador->actualizar_vida(this->puntos_de_vida);
        return true;
    }
    return false;
}

Type Sangre::getTipo(){
    return Type::sangre;
}
