#include "../include/textura.h"
#include <iostream>

Textura::Textura(const char *archivo, SDL_Renderer *un_render) {
    SDL_Surface *superficie = IMG_Load(archivo);
    SDL_Texture *unaTextura = SDL_CreateTextureFromSurface(un_render, superficie);
    if (!unaTextura || !superficie) {
        throw std::runtime_error("no se creo la textura");
    }
    SDL_FreeSurface(superficie);
    this->textura = unaTextura;
    this->render = un_render;
}

int Textura::renderizar(SDL_Rect *infoSprite, SDL_Rect destino, int angulo, SDL_Point *centro) const {
    try {
        return SDL_RenderCopyEx(this->render, this->textura, infoSprite, &destino, angulo, centro, SDL_FLIP_NONE);
    } catch (...) {
        std::cout << SDL_GetError();
    }
    return -1;
}
