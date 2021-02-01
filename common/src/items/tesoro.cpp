#include "items/tesoro.h"


Tesoro::Tesoro(int id, Type tipo,int puntos, Posicion &posicion) :
        Item(posicion, id),
        puntos(puntos),
        tipo(tipo){}

Tesoro::~Tesoro() {}

void Tesoro::obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) {
    jugador->sumarPuntos(this->puntos);
}

Type Tesoro::getTipo(){
    return this->tipo;
}
