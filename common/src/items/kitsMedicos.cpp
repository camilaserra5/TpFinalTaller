#include "items/kitsMedicos.h"

#define VIDA 20
#define VIDA_MAXIMA 100

KitsMedicos::KitsMedicos(Posicion &posicion, int id,int vidaMax,
                          int vidaKits) : Item(posicion, id),
                                          puntos_de_vida(vidaKits),
                                          maxPuntosDeVida(vidaMax){}

KitsMedicos::~KitsMedicos() {}

bool KitsMedicos::obtenerBeneficio(Jugador *jugador) {
    if (jugador->puntos_de_vida() != maxPuntosDeVida) {
        jugador->actualizar_vida(this->puntos_de_vida);
        return true;
    }
    return false;
}

Type KitsMedicos::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("kitsMedicos");
}
