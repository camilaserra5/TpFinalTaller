#include "../include/jugador.h"
// hay que verificar que la pos del jugador al incio sea random y valida;
#include <math.h>

#define MAX_VIDA 100
#define CANT_INICAL_BALAS 8

#include "armas/pistola.h"
#include "armas/cuchillo.h"
#include "../include/actualizaciones/actualizacionCambioArma.h"

#define PI 3.1415926
#define VELOCIDAD_DE_ROTACION 0.05  * PI

int Jugador::getId() {
    return this->id;
}

Jugador::Jugador(std::string &nombre, int &id, Posicion &posicion, float vidaMax, float vRotacion, int cantBalasInicial)
        :
        posicion(posicion),
        id(id),
        nombre(nombre),
        vida(vidaMax),
        armas(),
        balas(cantBalasInicial),
        velocidadDeRotacion(vRotacion),
        armaActual(ID_PISTOLA),
        llaves(0),
        cantidad_vidas(2),
        logro(),
        disparando(false) {
    std::cerr << "entro al constructor de jugador\n";
    this->armas.insert(std::make_pair(ID_PISTOLA, new Pistola()));
    this->armas.insert(std::make_pair(ID_CUCHILLO, new Cuchillo()));
    //this->armas.insert(std::make_pair(ID_AMETRALLADORA, new Ametralladora(posicion, ID_AMETRALLADORA)));
}

Jugador::Jugador() {
}

Jugador::~Jugador() {
    std::cerr << "entreee al destructor de Jugador " << this->id << std::endl;
    std::map<int, Arma *>::iterator it;
    for (auto &arm: this->armas) {
        delete arm.second;
    }

}

std::string Jugador::obtenerNombre() {
    return this->nombre;
}

// recibo la posicion a moverse
void Jugador::moverse(int posx, int posy) {
    this->posicion.actualizar_posicion(posx, posy);
}


// recibo cuando gano de vida + o cuanto pierdo -
void Jugador::actualizar_vida(int &vidaActualizada) {
    this->vida += vidaActualizada;
    if (this->vida > MAX_VIDA)
        this->vida = MAX_VIDA;
}

void Jugador::agregar_arma(Arma *arma) {
    this->armas.insert(std::make_pair(arma->getId(), arma));
}

bool Jugador::poseeArma(Arma *arma) {
    bool poseeArma = false;
    int cantidadArmas = this->armas.size();
    for (int i = 0; i < cantidadArmas; i++) {
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
    if (balas >= 0) {
        this->armaActual = ID_PISTOLA;
    }
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
    if (this->balas == 0) {
        std::cerr << "PASO A CUCHILLO";
        this->armaActual = ID_CUCHILLO;
    }
}

void Jugador::rotar(int sentido) {
    this->posicion.rotar(sentido * this->velocidadDeRotacion);
}

Logro &Jugador::obtenerLogro() {
    return this->logro;
}

void Jugador::gastarBalas(int cantidadDeBalas) {
    this->balas -= cantidadDeBalas;
    std::cerr << "cantidad de balas: " << this->balas << "\n";
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
    std::cerr << "=====reviviendo==========" << '\n';
    this->vida = MAX_VIDA;
    this->cantidad_vidas -= 1;
}

void Jugador::morir() {
    this->cantidad_vidas = 0;
    this->vida = 0;
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
    std::vector<char> sizeNombre = numberToCharArray(this->nombre.size());
    informacion.insert(informacion.end(), sizeNombre.begin(), sizeNombre.end());
    informacion.insert(informacion.end(), this->nombre.begin(), this->nombre.end());
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
    //std::cerr << " juegador deserializar empieza" << std::endl;
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->id = charArrayToNumber(sub);

    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    uint32_t longitudnombre = charArrayToNumber(sub);
    idx += 4;
    for (uint32_t k = 0; k < longitudnombre; k++) {
        this->nombre += serializado[idx++];
    }

    //std::cerr << " juegador deserializar id " << this->id << std::endl;
    //idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->vida = charArrayToNumber(sub);
    //std::cerr << " juegador deserializar vida " << this->vida << std::endl;
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->armaActual = charArrayToNumber(sub);
    std::cerr << " juegador deserializar armaActual " << this->armaActual << std::endl;
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->disparando = charArrayToNumber(sub);
    //std::cerr << " juegador deserializar disparando " << this->disparando << std::endl;
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->cantidad_vidas = charArrayToNumber(sub);
    //std::cerr << " juegador deserializar cantidad_vidas " << this->cantidad_vidas << std::endl;
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->balas = charArrayToNumber(sub);
    std::cerr << " juegador deserializar balas " << this->balas << std::endl;

    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    //std::cerr << "posicion: " << charArrayToNumber(sub);
    idx += 4;
    std::vector<char> posicionSerializado(serializado.begin() + idx,
                                          serializado.begin() + idx +
                                          charArrayToNumber(sub));
    this->posicion.deserializar(posicionSerializado);

    idx += charArrayToNumber(sub);
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    idx += 4;
    std::vector<char> logroSerializado(serializado.begin() + idx,
                                       serializado.begin() + idx +
                                       charArrayToNumber(sub));

    this->logro.deserializar(logroSerializado);
    //std::cerr << " juegador deserializar fin" << std::endl;

    this->armas.insert(std::make_pair(ID_PISTOLA, new Pistola()));
    this->armas.insert(std::make_pair(ID_CUCHILLO, new Cuchillo()));
}

void Jugador::dejarDeDisparar() {
    this->disparando = false;
}

void Jugador::atacar() {
    this->disparando = true;
}

Actualizacion *Jugador::cambiarArma() {
    std::map<int, Arma *>::iterator it;
    bool cambie = false;
    for (it = this->armas.begin(); it != this->armas.end(); ++it) {
        if (it->first != this->armaActual && !cambie) {
            this->armaActual = it->first;
            cambie = true;
        }
    }
    if (!cambie) {
        return NULL;
    }
    return new ActualizacionCambioArma(id, this->armaActual);
}
