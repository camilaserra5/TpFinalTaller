#include "../include/player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

#define VIDA_MAX 100
#define NIVEL 1
#define PUNTAJE_INICIAL 0
#define CANT_VIDA_MAX 3
#define BALAS_INICIAL 5

Player::Player(const char *rutaimg, SDL_Renderer *render, int id) :
        posicion(70, 70, 0),
        infoJugador(render, VIDA_MAX, NIVEL, PUNTAJE_INICIAL, CANT_VIDA_MAX, BALAS_INICIAL),
        id(id), arma(render), disparando(true) {

}

void Player::actualizar(int posx, int posy, int vida, float angulo, int idArma,
                        bool disparando, int puntaje, int cantVidas, int balas) {
    this->posicion.actualizar_posicion(posx, posy);
    this->posicion.setAngulo(angulo);
    this->arma.actualizar(idArma);
    this->disparando = disparando;
    this->infoJugador.actualizarDatosJugador(vida, 1, puntaje, cantVidas, balas);
}

void Player::renderizar() {
    this->arma.renderizar(disparando);
    this->infoJugador.renderizar();
}

Posicion &Player::getPosicion() {
    return this->posicion;
}

float Player::getAnguloDeVista() {
    return this->posicion.getAnguloDeVista();
}

int Player::getPuntaje() {
    return this->infoJugador.getPuntaje();
}

int Player::getId() {
    return id;
}

Player::~Player() {}
