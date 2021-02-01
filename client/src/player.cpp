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
        posx(0), posy(0),
        infoJugador(render, VIDA_MAX, NIVEL, PUNTAJE_INICIAL, CANT_VIDA_MAX, BALAS_INICIAL),
        angulo(50), id(id), arma(render), disparando(true) {

}

void Player::actualizar(int posx, int posy, int vida, int angulo, int idArma,
                        bool disparando, int puntaje,int cantVidas,int balas) {
    this->posx = posx;
    this->posy = posy;
    this->vida = vida;
    this->angulo = angulo;
    this->arma.actualizar(idArma);
    this->disparando = disparando;
    this->infoJugador.actualizarDatosJugador(vida, nivel, puntaje, cantVidas, balas);
}

void Player::renderizar() {
    this->arma.renderizar(disparando);
    this->infoJugador.renderizar();
}
