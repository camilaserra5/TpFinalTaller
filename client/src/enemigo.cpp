#include "../include/enemigo.h"
#include <config.h>

#define GUARDIA IMGS_DIR GUARD_IMG
#define RATA IMGS_DIR RAT_IMG
#define OFFICER IMGS_DIR OFFICER_IMG
#define MUTANTE IMGS_DIR MUTANT_IMG
#define ELITE_GUARD IMGS_DIR ELITE_GUARD_IMG
#define SPRITE_W 74.6
#define SPRITE_H 74
#define FRAMES_X 3
#define FRAMES_Y 4
#define MORIRSE 0
#define MOVERSE 1
#define DISPARAR 2
#define QUIETO 9

#define ID_CUCHILLO 3
#define ID_PISTOLA 4
#define ID_AMETRALLADORA 1
#define ID_LANZACOHETES 5
#define ID_CANION_DE_CADENA 2


Enemigo::Enemigo(SDL_Renderer *render, int idArmaJugador) :
        idArma(idArmaJugador), anguloJugador(0), estado(MOVERSE), distanciaParcialAJugador(0),
        posicion(0, 0, 0), enemigos(), puntaje(0) {
    // guardia
    Animacion dispararG(render, GUARDIA, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 0); // disparar
    Animacion moverseG(render, GUARDIA, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 1);
    Animacion morirseG(render, GUARDIA, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 2);

    std::vector<Animacion> guardia;
    guardia.push_back(morirseG);
    guardia.push_back(moverseG);
    guardia.push_back(dispararG);

    Animacion dispararR(render, RATA, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 0);
    Animacion moverseR(render, RATA, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 1);
    Animacion morirseR(render, RATA, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 2);

    std::vector<Animacion> rata;
    rata.push_back(morirseR);
    rata.push_back(moverseR);
    rata.push_back(dispararR);

    Animacion dispararM(render, MUTANTE, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 0);
    Animacion moverseM(render, MUTANTE, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 1);
    Animacion morirseM(render, MUTANTE, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 2);

    std::vector<Animacion> mutante;
    mutante.push_back(morirseM);
    mutante.push_back(moverseM);
    mutante.push_back(dispararM);

    Animacion dispararO(render, OFFICER, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 0);
    Animacion moverseO(render, OFFICER, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 1);
    Animacion morirseO(render, OFFICER, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 2);

    std::vector<Animacion> officer;
    officer.push_back(morirseO);
    officer.push_back(moverseO);
    officer.push_back(dispararO);

    Animacion dispararEG(render, ELITE_GUARD, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 0);
    Animacion moverseEG(render, ELITE_GUARD, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 1);
    Animacion morirseEG(render, ELITE_GUARD, FRAMES_Y, SPRITE_H, SPRITE_W, -1, 2);

    std::vector<Animacion> elite_guard;
    elite_guard.push_back(morirseEG);
    elite_guard.push_back(moverseEG);
    elite_guard.push_back(dispararEG);

    this->enemigos.insert(std::make_pair(ID_PISTOLA, guardia));
    this->enemigos.insert(std::make_pair(ID_CUCHILLO, rata));
    this->enemigos.insert(std::make_pair(ID_LANZACOHETES, mutante));
    this->enemigos.insert(std::make_pair(ID_CANION_DE_CADENA, officer));
    this->enemigos.insert(std::make_pair(ID_AMETRALLADORA, elite_guard));
}

Enemigo::~Enemigo() {}

void Enemigo::actualizar(int posx, int posy, int idArmaJugador,
                         int anguloEnemigo, int anguloJugador, int vida,
                         bool disparando, int puntaje) {
    Posicion posicionNueva(posx, posy, 0);
    verificarEstado(posicionNueva, vida, disparando);
    this->posicion.actualizar_posicion(posx, posy);
    this->posicion.setAngulo(anguloEnemigo);
    this->idArma = idArmaJugador;
    this->anguloJugador = anguloJugador;
    this->puntaje = puntaje;
}

void Enemigo::verificarEstado(Posicion &posicionNueva, int vida, bool disparando) {
    if (disparando) {
        this->estado = DISPARAR;
    } else if (vida <= 0) {
        this->estado = MORIRSE;
    } else if (!(this->posicion == posicionNueva)) {
        this->estado = MOVERSE;
    } else {
        this->estado = QUIETO;
    }
}

void Enemigo::renderizar() {
    std::vector<Animacion> &tipo = this->enemigos.find(this->idArma)->second;
    tipo[this->estado].renderizar(this->posicion.pixelesEnX(), this->posicion.pixelesEnY(), 0, NULL);
}


Posicion &Enemigo::getPosicion() {
    return this->posicion;
}

void Enemigo::renderizarColumna(SDL_Rect &dimension, SDL_Rect &dest) {
    std::vector<Animacion> &tipo = this->enemigos.find(this->idArma)->second;
    tipo[this->estado].renderizarColumna(dimension, dest);
}

void Enemigo::actualizarVida(int vida) {
    if (vida <= 0) {
        this->estado = MORIRSE;
    }
}

int Enemigo::obtenerAnchura() {
    return SPRITE_W;
}

void Enemigo::actualizarPosicion(int posX, int posY, float angulo) {
    this->posicion.actualizar_posicion(posX, posY);
    this->posicion.setAngulo(angulo);
}
