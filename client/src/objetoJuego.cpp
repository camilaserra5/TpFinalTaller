#include "../include/objetoJuego.h"

ObjetoJuego::ObjetoJuego(Sprite sprite) :
        sprite(sprite),
        posx(0), posy(0),
        angulo(0){}

ObjetoJuego::~ObjetoJuego(){}

void ObjetoJuego::renderizar() {
    this->sprite.renderizar(this->posx, this->posy, this->angulo);
}

void ObjetoJuego::settear_estado(int posx, int posy){
    this->posx = posy;
    this->posy = posy;
}
