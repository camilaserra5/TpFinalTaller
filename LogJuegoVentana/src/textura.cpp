#include "../include/textura.h"
#include "../include/lienzo.h"

Textura::Textura(const char *archivo, SDL_Renderer *un_render) {
    SDL_Surface *superficie = IMG_Load(archivo);
    SDL_Texture *unaTextura = SDL_CreateTextureFromSurface(un_render, superficie);
    if (!unaTextura || !superficie) {
        throw -1;//SdlException("Error al cargar la textura", SDL_GetError());
    }
    SDL_FreeSurface(superficie);
    this->textura = unaTextura;
}

int Textura::renderizar(const Lienzo& src, const Lienzo& dest) const {
    SDL_Rect sdlSrc = {
            src.getX(), src.getY(),
            src.getAncho(), src.getAlto()
    };
    SDL_Rect sdlDest = {
            dest.getX(), dest.getY(),
            dest.getAncho(), dest.getAlto()
    };
    return SDL_RenderCopy(this->render, this->textura, &sdlSrc, &sdlDest);
}