#include "../include/juego.h"
#include "../include/textura.h"
#define EXITO 0


void Juego::inicializar(const char* titulo, int xpos, int ypos, int ancho, int alto, bool fullscreen){
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == EXITO) {
        this->ventana = SDL_CreateWindow(titulo, xpos,ypos, ancho, alto, flags);
        this->render = SDL_CreateRenderer(this->ventana,-1,0);
        SDL_SetRenderDrawColor(this->render, 157 , 97, 70, 255);
        this->corriendo = true;
    } else {
        this->corriendo = false;
    }
    Textura* unaTextura = new Textura("..resources/images/ParteInferior.png", this->render);
    this->texturaInferior = unaTextura->cargarTextura();
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
    SDL_Rect posiciontexturaini = {0,0, 300, 300};
    SDL_Rect posiciontexturadest = {100, 100, 300, 300 };
    SDL_RenderCopy(this->render, this->texturaInferior, &posiciontexturaini, &posiciontexturadest);
    SDL_RenderPresent(this->render);
}

void Juego::clean(){
    SDL_DestroyWindow(this->ventana);
    SDL_DestroyRenderer(this->render);
    SDL_Quit();
}
