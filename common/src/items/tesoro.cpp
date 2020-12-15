#include "items/tesoro.h"


Tesoro::Tesoro(std::string& tipoDeTesoro, int& puntos,Posicion &posicion):
    Item(posicion),
    tipoDeTesoro(tipoDeTesoro),
    puntos(puntos){}

Tesoro::~Tesoro(){}

void Tesoro::obtenerBeneficio(Jugador* jugador){
    jugador->sumarPuntos(this->puntos);
}
