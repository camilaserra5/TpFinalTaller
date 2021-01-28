#include "../include/player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>


Player::Player(const char* rutaimg, SDL_Renderer* render, int id):
            posx(0), posy(0), vida(100), angulo(50), id(id){
        Sprite spriteCuchillo = Sprite(render, rutaimg, 1, 0, 65, 60);
        Sprite spritePistola = Sprite(render, rutaimg, 0, 1, 65, 60);
        Sprite spriteAmetralladora = Sprite(render, rutaimg, 0, 2, 65, 60);
        Sprite spriteCanion = Sprite(render, rutaimg, 0, 3, 65, 60);
        this->sprites.insert(std::make_pair(3, spriteCuchillo));
        this->sprites.insert(std::make_pair(4, spritePistola));
        this->sprites.insert(std::make_pair(1, spriteAmetralladora));
        this->sprites.insert(std::make_pair(2, spriteCanion));
}
void Player::settear_estado(int posx, int posy, int vida, int angulo, int idArma){
        this->posx = posx;
        this->posy = posy;
        this->vida = vida;
        this->angulo = angulo;
        this->idArmaActual = idArma;
}
void Player::renderizar(){
        this->sprites.find(this->idArmaActual)->second.renderizar(this->posx, this->posy, this->angulo);
}

void Player::actualizacion(int posx, int posy, int vida, int angulo, int arma){
    settear_estado(posx, posy, vida, angulo, arma);
    renderizar();
}