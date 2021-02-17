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
    this->contador = 60;
}

Animacion::~Animacion() {}

void Animacion::renderizar(int posx, int posy, int angulo, SDL_Point *centro) {
    int cantFrames = frames.size();
    if (this->frameActual >= cantFrames) {
        this->frameActual = 0;
    }
    SDL_Rect r = {posx, posy, this->frame_h * 2, this->frame_w * 2}; // Donde se renderiza
    textura->renderizar(&frames[this->frameActual], r, angulo, centro);
    if (contador == 0){
        this->frameActual += 1;
    }
    contador--;
  //  SDL_Delay(100);

}

void Animacion::renderizarColumna(SDL_Rect &dimension, SDL_Rect dest) {
    int cantFrames = frames.size();
    if (this->frameActual >= cantFrames) {
        this->frameActual = 0;
    }
    dimension.x += this->frames[frameActual].x;
    dimension.y += this->frames[frameActual].y;
    dimension.h += this->frame_h;
    dest.y -= 30;
  //  std::cerr << "renderizo animacion con dimensiones x: " << dimension.x << " y: " << dimension.y << " h: " << dimension.h << " w: " << dimension.w << std::endl << std::endl;
    //std::cerr << "renderizo animacion en x: " << dest.x << " y: " << dest.y << " h: " << dest.h << " w: " << dest.w << std::endl << std::endl;
    this->textura->renderizar(&dimension, dest, 0, NULL);
    if (contador == 0){
        this->frameActual += 1;
    }
    contador--;
}
