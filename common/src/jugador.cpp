#include "../include/jugador.h"
// hay que verificar que la pos del jugador al incio sea random y valida;
#include <iostream>
#include <math.h>
#define MAX_VIDA 100
#define POSX_INICIAL 5
#define POSY_INICIAL 5
#define CANT_INICAL_BALAS 8
#include "armas/pistola.h"
#include "armas/lanzacohetes.h"
#include "objetosJuego.h"
#define VELOCIDAD_DE_ROTACION 0.25 * acos(0.0)

int Jugador::getId() {
    return this->id;
}

Jugador::Jugador(std::string &nombre, int &id) :
//posicion(posicion), que lo reciba inicializado por parametro
        nombre(nombre),
        id(id),
        vida(MAX_VIDA),
        armas(),
        balas(CANT_INICAL_BALAS),
        armaActual(ID_PISTOLA),
        posicion(POSX_INICIAL, POSY_INICIAL, 50),
        velocidadDeRotacion(VELOCIDAD_DE_ROTACION),
        llaves(0),
        cantidad_vidas(2),
        disparando(false) {
            this->armas.insert(std::make_pair(armaActual, new Pistola(10)));
        }

Jugador::~Jugador() {
    std::cout << "destructor jugador";
    for (int i = 0; i < this->armas.size(); i++) {
        //  delete armas[i];
    }
    std::cout << "entro\n";
}

// recibo la posicion a moverse
void Jugador::moverse(int posx, int posy) {

    this->posicion.actualizar_posicion(posx, posy);
}


// recibo cuando gano de vida + o cuanto pierdo -
void Jugador::actualizar_vida(int &vidaActualizada) {
    this->vida += vidaActualizada;
}

void Jugador::agregar_arma(Arma *arma) {
    this->armas.insert(std::make_pair(arma->getId(),arma));
}

bool Jugador::poseeArma(Arma *arma) {
    bool poseeArma = false;
    for (int i = 0; i < this->armas.size(); i++) {
        if (this->armas[i]->esIgual(arma)) {
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
    return this->posicion.pixelesEnX();
}

int Jugador::posEnY() {
    return this->posicion.pixelesEnY();
}

void Jugador::sumarPuntos(int puntos) {
    this->logro.aniadirPuntosPorTesoro(puntos);
}

void Jugador::agarrarLlave() {
    this->llaves += 1;
}

void Jugador::actualizarArma(){
  Posicion posDefault(0,0,0);
  Arma* lanzacohetes = new LanzaCohetes(posDefault, static_cast<int>(Type::lanzaCohetes));
  if (this->balas < BALAS_PARA_LANZACOHETES && this->armas.at(this->armaActual)->esIgual(lanzacohetes) && this->balas > 0){
      this->armaActual = ID_PISTOLA;
  }else{
    this->armaActual = ID_CUCHILLO;
  }
  //delete lanzacohetes;
}

void Jugador::rotar(int sentido) {
    this->posicion.rotar(sentido * this->velocidadDeRotacion);
}

Logro &Jugador::obtenerLogro() {
    return this->logro;
}

void Jugador::gastarBalas(int cantidadDeBalas) {
    this->balas -= cantidadDeBalas;
    this->logro.aniadirBalasDisparadas(cantidadDeBalas);
}

float Jugador::getAnguloDeVista() { return this->posicion.getAnguloDeVista(); }

Arma *Jugador::getArma() { return this->armas.find(this->armaActual)->second; }

void Jugador::setPosicion(Posicion &posicion) { this->posicion = posicion; }

Posicion &Jugador::getPosicion() { return this->posicion; }

bool Jugador::tengollave() {
    return (this->llaves > 0);
}

void Jugador::usarLlave() {
    this->llaves += -1;
}

bool Jugador::estaMuerto() {
    return (this->vida <= 0);
}

void Jugador::aniadirEnemigosMatados(int jugadoresMatados) {
    this->logro.aniadirEnemigosMatados(jugadoresMatados);
}

bool Jugador::estaDisparando(){
    this->disparando;
}
