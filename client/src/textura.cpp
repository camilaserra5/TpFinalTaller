#include "../include/textura.h"

Textura::Textura(const char *archivo, SDL_Renderer *un_render) {
    SDL_Surface *superficie = IMG_Load(archivo);
    SDL_Texture *unaTextura = SDL_CreateTextureFromSurface(un_render, superficie);
    if (!unaTextura || !superficie) {
        throw -1;//Exception("Error al cargar la textura", SDL_GetError());
    }
    SDL_FreeSurface(superficie);
    this->textura = unaTextura;
    this->render = un_render;
}

int Textura::renderizar(SDL_Rect *infoSprite, SDL_Rect destino) const {

    return SDL_RenderCopy(this->render, this->textura, infoSprite, &destino);
}
