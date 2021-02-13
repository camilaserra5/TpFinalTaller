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
#include "../include/actualizaciones/actualizacionCambioArma.h"


#define VELOCIDAD_DE_ROTACION 0.25 * acos(0.0)

int Jugador::getId() {
    return this->id;
}

Jugador::Jugador(std::string &nombre, int &id, Posicion &posicion) :
        posicion(posicion),
        nombre(nombre),
        id(id),
        vida(MAX_VIDA),
        armas(),
        balas(CANT_INICAL_BALAS),
        armaActual(ID_PISTOLA),
        velocidadDeRotacion(VELOCIDAD_DE_ROTACION),
        llaves(0),
        cantidad_vidas(2),
        disparando(false) {
    this->armas.insert(std::make_pair(armaActual, new Pistola()));
}

Jugador::Jugador() {
}

Jugador::~Jugador() {

    /*  for (int i = 0; i < this->armas.size(); i++) {
            delete armas[i];
      }*/

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
    this->armas.insert(std::make_pair(arma->getId(), arma));
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

void Jugador::actualizarArma() {
    Posicion posDefault(0, 0, 0);
    Arma *lanzacohetes = new LanzaCohetes(posDefault,
                                          ObjetosJuego::obtenerTipoPorNombre("lanzaCohetes").getType());
    if (this->balas < BALAS_PARA_LANZACOHETES &&
        this->armas.at(this->armaActual)->esIgual(lanzacohetes) &&
        this->balas > 0) {
        this->armaActual = ID_PISTOLA;
    } else {
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

bool Jugador::estaDisparando() {
    return this->disparando;
}

void Jugador::actualizarNuevaVida() {
    this->vida = MAX_VIDA;
    this->cantidad_vidas -= 1;
}

int Jugador::cant_de_vida() {
    return this->cantidad_vidas;
}

int Jugador::obtenerPuntosTotales() {
    return this->logro.obtenerPuntosTotales();
}

std::vector<char> Jugador::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->id);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(this->vida);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(this->armaActual);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(this->disparando);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(this->cantidad_vidas);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(this->balas);
    informacion.insert(informacion.end(), aux.begin(), aux.end());

    std::vector<char> posicionSerializado = this->posicion.serializar();
    aux = numberToCharArray(posicionSerializado.size());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    informacion.insert(informacion.end(), posicionSerializado.begin(),
                       posicionSerializado.end());

    std::vector<char> logroSerializado = this->logro.serializar();
    aux = numberToCharArray(logroSerializado.size());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    informacion.insert(informacion.end(), logroSerializado.begin(),
                       logroSerializado.end());

    return informacion;
}

void Jugador::deserializar(std::vector<char> &serializado) {
    std::cerr << " juegador deserializar empieza" << std::endl;
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->id = charArrayToNumber(sub);
    std::cerr << " juegador deserializar id " << this->id << std::endl;
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->vida = charArrayToNumber(sub);
    std::cerr << " juegador deserializar vida " << this->vida << std::endl;
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->armaActual = charArrayToNumber(sub);
    std::cerr << " juegador deserializar armaActual " << this->armaActual << std::endl;
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->disparando = charArrayToNumber(sub);
    std::cerr << " juegador deserializar disparando " << this->disparando << std::endl;
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->cantidad_vidas = charArrayToNumber(sub);
    std::cerr << " juegador deserializar cantidad_vidas " << this->cantidad_vidas << std::endl;
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->balas = charArrayToNumber(sub);
    std::cerr << " juegador deserializar balas " << this->balas << std::endl;

    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    std::cerr << "posicion: " << charArrayToNumber(sub);
    std::vector<char> posicionSerializado(serializado.begin() + idx,
                                          serializado.begin() + idx +
                                          charArrayToNumber(sub));
    this->posicion.deserializar(posicionSerializado);

    idx += 4;
    idx += charArrayToNumber(sub);
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);

    std::vector<char> logroSerializado(serializado.begin() + idx,
                                       serializado.begin() + idx +
                                       charArrayToNumber(sub));

    this->logro.deserializar(logroSerializado);
    std::cerr << " juegador deserializar fin" << std::endl;

    armaActual = ID_PISTOLA;
    this->armas.insert(std::make_pair(armaActual, new Pistola()));
}

void Jugador::dejarDeDisparar() {
    this->disparando = false;
}

void Jugador::atacar() {
    this->disparando = true;
}

Actualizacion* Jugador::cambiarArma() {
    std::map<int, Arma *>::iterator it;
    bool cambie = false;
    for (it = this->armas.begin(); it != this->armas.end(); ++it) {
        if (it->first != this->armaActual && !cambie) {
            this->armaActual = it->first;
            cambie = true;
        }
    }
    if (!cambie){
        return NULL;
    }
    return new ActualizacionCambioArma(id, this->armaActual);
}
