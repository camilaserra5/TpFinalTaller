#include "../include/jugador.h"

Jugador::Jugador():
    vida(100),
    posx(50),
    posy(50),
    municiones(8),
    armas(),
    puntaje(0){}

Jugador::~Jugador(){}

// recibo la posicion a moverse
void Jugador::moverse(int &posx, int &posy){
    this->posx += posx;
    this->posy += posy;
}
// recibo cuando gano de vida + o cuanto pierdo -
void Jugador::actualizar_vida(int &vidaActualizada){
    this->vida += vidaActualizada;
}

void Jugador::agregar_arma(Arma* arma){
    this->armas.push_back(arma);
}
