#include "../include/juego.h"

#define EXITO 0


void Juego::inicializar(const char *titulo, int xpos, int ypos, int ancho, int alto, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == EXITO) {
        this->ventana = SDL_CreateWindow(titulo, xpos, ypos, ancho, alto, flags);
        this->render = SDL_CreateRenderer(this->ventana, -1, 0);
        SDL_SetRenderDrawColor(this->render, 157, 97, 70, 255);
        SDL_RenderClear(this->render);
        this->corriendo = true;
    } else {
        this->corriendo = false;
    }
    this->texturaInferior = new Textura("../../LogJuegoVentana/resources/images/ParteInferior.png", this->render);
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

void Juego::actualizar() {}

void Juego::renderizar() {
    SDL_RenderClear(this->render);
    Lienzo posiciontexturaini(0, 0, 800, 40);
    Lienzo posiciontexturadest(0, 562, 800, 40);
    this->texturaInferior->renderizar(this->render, posiciontexturaini, posiciontexturadest);
    SDL_RenderPresent(this->render);
}

void Juego::clean() {
    SDL_DestroyWindow(this->ventana);
    SDL_DestroyRenderer(this->render);
    SDL_Quit();
}
