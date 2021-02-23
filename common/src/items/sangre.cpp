#include "items/sangre.h"

//#define VIDA 1
//#define VIDA_MAXIMA 11

Sangre::Sangre(Posicion &posicion, int id, int vidaMax, int puntosDeVidaSangre)
                : Item(posicion, id), puntos_de_vida(puntosDeVidaSangre),
                  maxPuntosDeVida(vidaMax){}

Sangre::~Sangre() {}

bool Sangre::obtenerBeneficio(Jugador *jugador) {
    if (jugador->puntos_de_vida() <= maxPuntosDeVida) {
        jugador->actualizar_vida(this->puntos_de_vida);
        return true;
    }
    return false;
}

Type Sangre::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("sangre");
}
