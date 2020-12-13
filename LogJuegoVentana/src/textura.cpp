#include "../include/textura.h"

Textura::Textura(const char *archivo, SDL_Renderer *un_render) {
    SDL_Surface *superficie = IMG_Load(archivo);
    SDL_Texture *unaTextura = SDL_CreateTextureFromSurface(un_render, superficie);
    if (!unaTextura || !superficie) {
        throw -1;//SdlException("Error al cargar la textura", SDL_GetError());
    }
    SDL_FreeSurface(superficie);
    this->textura = unaTextura;
}

<<<<<<< HEAD
SDL_Texture *Textura::cargarTextura() {
    return this->textura;
}
=======
int Textura::renderizar(SDL_Renderer* render, const Lienzo& src, const Lienzo& dest) const {
    SDL_Rect sdlSrc = {
            src.getX(), src.getY(),
            src.getAncho(), src.getAlto()
    };
    SDL_Rect sdlDest = {
            dest.getX(), dest.getY(),
            dest.getAncho(), dest.getAlto()
    };
    return SDL_RenderCopy(render, this->textura, &sdlSrc, &sdlDest);
}
>>>>>>> 41293b1723feb628b3ba72462c3bec0cc3dda179
