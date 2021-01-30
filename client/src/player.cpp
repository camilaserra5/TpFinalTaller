#include "../include/player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>


Player::Player(const char *rutaimg, SDL_Renderer *render, int id) :
        posx(0), posy(0), vida(100), nivel(1), puntaje(50), cantVidas(3),
        infoJugador(render, vida, nivel, puntaje, cantVidas), angulo(50),
        id(id), arma(render), disparando(true) {

}

void Player::settear_estado(int posx, int posy, int vida, int angulo, int idArma) {
    this->posx = posx;
    this->posy = posy;
    this->vida = vida;
    this->angulo = angulo;
    this->arma.actualizar(idArma);
    this->infoJugador.actualizarDatosJugador(vida, nivel, puntaje, this->cantVidas);
}

void Player::renderizar() {
    this->arma.renderizar(disparando);
    this->infoJugador.renderizar();
}

void Player::actualizacion(int posx, int posy, int vida, int angulo, int arma) {
      settear_estado(posx, posy, vida, angulo, arma);
}
