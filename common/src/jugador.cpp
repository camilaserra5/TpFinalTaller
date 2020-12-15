#include "../include/jugador.h"
// hay que verificar que la pos del jugador al incio sea random y valida;
#include <iostream>

#define MAX_VIDA 100
#define POSX_INICIAL 5
#define POSY_INICIAL 5
#define CANT_INICAL_BALAS 8
#define PUNTAJE_INICIAL 0

#include "armas/cuchillo.h"

int Jugador::getId() {
    return this->id;
}

Jugador::Jugador(std::string& nombre, int& id) :
        //posicion(posicion), que lo reciba inicializado por parametro
        nombre(nombre),
        id(id),
        vida(MAX_VIDA),
        posx(POSX_INICIAL),
        posy(POSY_INICIAL),
        armas(),
        puntaje(PUNTAJE_INICIAL),
        balas(CANT_INICAL_BALAS),
        armaActual(new Cuchillo()),
        posicion(posx, posy, 50),
        llaves(0),
        cantidad_vidas(2){}

Jugador::~Jugador() {
    std::cout << "destructor jugador";
    for (int i = 0; i < this->armas.size(); i++) {
        //  delete armas[i];
    }
    delete this->armaActual;
    std::cout << "entro\n";
}

// recibo la posicion a moverse
void Jugador::moverse(int posx, int posy) {
    this->posx += posx;
    this->posy += posy;
    std::cout << "x: " << posx;
    std::cout << "y: " << posy;
}


// recibo cuando gano de vida + o cuanto pierdo -
void Jugador::actualizar_vida(int &vidaActualizada) {
    this->vida += vidaActualizada;
}

void Jugador::agregar_arma(Arma *arma) {
    this->armas.push_back(arma);
}

bool Jugador::poseeArma(Arma* arma){
      bool poseeArma = false;
      for (int i =0; i< this->armas.size(); i++){
            if (this->armas[i]->esIgual(arma)){
                poseeArma = true;
            }
      }
      return poseeArma;
}
int Jugador::puntos_de_vida() {
    return this->vida;
}

int Jugador::cantidad_balas() {
    return this->balas;
}

void Jugador::agregar_balas(int &balas) {
    this->balas += balas;
}

int Jugador::posEnX() {
    return this->posx;
}

int Jugador::posEnY() {
    return this->posy;
}

void Jugador::sumarPuntos(int puntos){
    this->puntaje += puntos;
}

void Jugador::agarrarLlave(){
    this->llaves +=1;
}
