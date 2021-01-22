#include "items/comida.h"
#include <iostream>

#define VIDA 10
#define VIDA_MAXIMA 100

Comida::Comida(Posicion &posicion) : Item(posicion), puntos_de_vida(VIDA) {}

Comida::~Comida() {}

void Comida::obtenerBeneficio(ContenedorDeElementos &contenedor,Jugador *jugador) {
    std::cout << "obtuve beneficio comida";
    if (jugador->puntos_de_vida() != VIDA_MAXIMA) {
        jugador->actualizar_vida(this->puntos_de_vida);
        //this->sacarDelMapa(contenedor);
      //  contenedor.sacarElementoDePosicion(this->posicion);
    }
}
