#include "../include/animacion.h"


Animacion::Animacion(SDL_Renderer *render,
                     const char *rutaimg,
                     int frames,
                     int frame_h,
                     int frame_w,
                     int fila, int columna) {

    if (fila > -1) {
        SDL_Rect rect = {0, fila * frame_h, frame_h, frame_w};
        for (int i = 0; i < frames; i++) {
            this->frames.push_back(rect);
            rect.x += frame_w;
        }
    } else {
        SDL_Rect rect = {columna * frame_w, 0, frame_h, frame_w};
        for (int i = 0; i < frames; i++) {
            this->frames.push_back(rect);
            rect.y += frame_h;
        }
    }
    this->textura = new Textura(rutaimg, render);
    this->frame_h = frame_h;
    this->frame_w = frame_w;
    this->frameActual = 0;
    this->velocidad = 1000;
    this->tiempoViejo = 0;
}

Animacion::~Animacion() {
    //  delete this->textura;
}

void Animacion::renderizar(int posx, int posy, int angulo, SDL_Point *centro) {

    if (tiempoViejo + velocidad > SDL_GetTicks()) {

    }
    tiempoViejo = SDL_GetTicks();

    if (this->frameActual >= frames.size()) {
        this->frameActual = 0;
    }
    SDL_Rect r = {posx, posy, this->frame_h * 2, this->frame_w * 2}; // Donde se renderiza
    textura->renderizar(&frames[this->frameActual], r, angulo, centro);
    this->frameActual += 1;
    SDL_Delay(100);

}

void Animacion::renderizarColumna(SDL_Rect &dimension, SDL_Rect dest) {
    this->textura->renderizar(&dimension, dest, 0, NULL);
}
