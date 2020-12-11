#include "../include/jugador.h"
// hay que verificar que la pos del jugador al incio sea random y valida;
#include <iostream>
Jugador::Jugador():
    vida(100),
    posx(5),
    posy(5),
    municiones(8),
    armas(),
    puntaje(0){}

Jugador::~Jugador(){}

// recibo la posicion a moverse
void Jugador::moverse(int posx, int posy){
    this->posx += posx;
    this->posy += posy;
    std::cout << "x: " <<posx;
    std::cout << "y: " << posy;
}
// recibo cuando gano de vida + o cuanto pierdo -
void Jugador::actualizar_vida(int &vidaActualizada){
    this->vida += vidaActualizada;
}

void Jugador::agregar_arma(Arma* arma){
    this->armas.push_back(arma);
}

int Jugador::posEnX(){
    return this->posx;
}

int Jugador::posEnY(){
    return this->posy;
}
