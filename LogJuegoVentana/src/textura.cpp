#include "../include/textura.h"

Textura::Textura(const char* archivo, SDL_Renderer* un_render){
    SDL_Surface* superficie = IMG_Load(archivo);
    SDL_Texture* unaTextura = SDL_CreateTextureFromSurface(un_render, superficie);

    SDL_FreeSurface(superficie);
    this->textura = unaTextura;
}

SDL_Texture* Textura::cargarTextura(){
    return this->textura;
}
