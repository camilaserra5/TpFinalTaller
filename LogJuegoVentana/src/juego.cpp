#include "../include/juego.h"
#define EXITO 0

void Juego::inicializar(const char* titulo, int xpos, int ypos, int ancho, int alto, bool fullscreen){
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == EXITO) {
        this->ventana = SDL_CreateWindow(titulo, xpos,ypos, ancho, alto, flags);
        this->render = SDL_CreateRenderer(this->ventana,-1,0);
        SDL_SetRenderDrawColor(this->render, 255 , 0, 0, 255);
        this->corriendo = true;
    } else {
        this->corriendo = false;
    }
}

void Juego::handleEvents() {
    SDL_Event evento;
    SDL_PollEvent(&evento);
    switch (evento.type) {
        case SDL_QUIT:
            this->corriendo = false;
            break;

        default:
            break;
    }
}

void Juego::actualizar(){}

void Juego::renderizar(){
    SDL_RenderClear(this->render);
    SDL_RenderPresent(this->render);
}

void Juego::clean(){
    SDL_DestroyWindow(this->ventana);
    SDL_DestroyRenderer(this->render);
    SDL_Quit();
}