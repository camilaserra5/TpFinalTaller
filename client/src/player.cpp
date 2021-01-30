#include "../include/player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>


Player::Player(const char *rutaimg, SDL_Renderer *render, int id) :
        posx(0), posy(0), vida(100), nivel(1), puntaje(50), cantVidas(3),
        infoJugador(render, vida, nivel, puntaje, cantVidas), angulo(50),
        id(id), idArmaActual(4), animacion(render, rutaimg, 5, 65, 60, 2), disparando(true) {
    Sprite spriteCuchillo = Sprite(render, rutaimg, 1, 0, 65, 60);
    Sprite spritePistola = Sprite(render, rutaimg, 0, 1, 65, 60);
    Sprite spriteAmetralladora = Sprite(render, rutaimg, 0, 2, 65, 60);
    Sprite spriteCanion = Sprite(render, rutaimg, 0, 3, 65, 60);
    this->sprites.insert(std::make_pair(3, spriteCuchillo));
    this->sprites.insert(std::make_pair(4, spritePistola));
    this->sprites.insert(std::make_pair(1, spriteAmetralladora));
    this->sprites.insert(std::make_pair(2, spriteCanion));
}

void Player::settear_estado(int posx, int posy, int vida, int angulo, int idArma) {
    this->posx = posx;
    this->posy = posy;
    this->vida = vida;
    this->angulo = angulo;
    this->idArmaActual = idArma;
    this->infoJugador.actualizarDatosJugador(vida, nivel, puntaje, this->cantVidas);
}

void Player::renderizar() {

    if(disparando){
          bool termine = this->animacion.renderizar(this->posx, this->posy);
          termine ? this->disparando = false: this->disparando = true;

    } else {

        this->sprites.find(this->idArmaActual)->second.reescalar(2, 2);
        this->sprites.find(this->idArmaActual)->second.renderizar(this->posx, this->posy, this->angulo);
    }

    this->infoJugador.renderizar();
}

void Player::actualizacion(int posx, int posy, int vida, int angulo, int arma) {
    settear_estado(posx, posy, vida, angulo, arma);
}
