#include "items/comida.h"

//#define VIDA 10
//#define VIDA_MAXIMA 100

Comida::Comida(Posicion &posicion, int id, int puntosVidaComida,
              int puntosDeVidaMax) : Item(posicion, id),
                                      puntos_de_vida(puntosVidaComida),
                                    puntosDeVidaMax(puntosDeVidaMax){}

Comida::~Comida() {}

bool Comida::obtenerBeneficio(Jugador *jugador) {
    if (jugador->puntos_de_vida() != puntosDeVidaMax) {
        jugador->actualizar_vida(this->puntos_de_vida);
        return true;
    }
    return false;
}

Type Comida::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("comida");
}
