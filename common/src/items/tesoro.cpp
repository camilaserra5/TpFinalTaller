#include "items/tesoro.h"


Tesoro::Tesoro(int id, int puntos, Posicion &posicion) :
        Item(posicion, id),
        puntos(puntos) {}

Tesoro::~Tesoro() {}

void Tesoro::obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) {
    jugador->sumarPuntos(this->puntos);
}
