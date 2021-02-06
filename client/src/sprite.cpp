#include "../include/sprite.h"
#include "../include/textura.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Sprite::Sprite(SDL_Renderer *render, const char *rutaimg, int x, int y, int h, int w) {
    this->infoSprite.x = x * w;
    this->infoSprite.y = y * h;
    this->infoSprite.w = w;
    this->infoSprite.h = h;
    this->destino.h = h * 2;
    this->destino.w = w * 2;
    this->textura = new Textura(rutaimg, render);
}

void Sprite::renderizar(int x, int y, int angulo, SDL_Point *centro) {
    this->destino.x = x;
    this->destino.y = y;
    this->textura->renderizar(&this->infoSprite, this->destino, angulo, centro);
}

void Sprite::renderizarColumna(SDL_Rect dimension, SDL_Rect &dest) {
    dimension.x += this->infoSprite.x + 2;
    dimension.y += this->infoSprite.y;//cheqeuar
//  std::cout << "x: " << dimension.x << " y " <<dimension.y <<"\n";
    this->textura->renderizar(&dimension, dest, 0, NULL);
}

void Sprite::reescalar(int escalarw, int escalarh) {
    this->destino.h = this->destino.h * escalarh;
    this->destino.w = this->destino.w * escalarw;
}
