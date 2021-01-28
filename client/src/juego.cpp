#include "../include/juego.h"
#define EXITO 0
#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL.h>

Juego::Juego(const std::string& titulo, int ancho, int alto, bool fullscreen, int idJugador) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == EXITO) {


        if (TTF_Init() == -1) {
            printf("Failed to init TTF\n");
            exit(1);
        }

        this->ventana =  new Ventana(titulo, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ancho, alto, flags);
        this->modelo = new Modelo(this->ventana, idJugador);
        modelo->inicializar(); // recibiria el yaml
        this->texturaInferior = new Textura("../../client/resources/images/ParteInferior.png", this->ventana->obtener_render());
        this->corriendo = true;
    } else {
        this->corriendo = false;
    }


    //ObjetoJuego *enemigo = new ObjetoJuego("../../client/resources/images/Guard.png", this->ventana->obtener_render(),  /*50, 50,*/0, 0, 78, 78/*100,100*/);
    //this->objetos.push_back(enemigo);
}

void Juego::run(){
    this->clean();
    this->renderizar();
    this->actualizar(/*1*/);

}
void Juego::actualizar(/*temporal int idArma*/) {
    //this->objetos.front()->actualizar();
    this->ventana->actualizar();
}

void Juego::renderizar() {
    this->ventana->renderizar(this->texturaInferior);
    this->modelo->renderizar();

  /*  SDL_RenderClear(this->render);
    Lienzo posiciontexturaini(0, 0, 800, 40);
    Lienzo posiciontexturadest(0, 562, 800, 40);
    this->texturaInferior->renderizar(this->render
  , posiciontexturaini, posiciontexturadest);
    this->objetos.front()->renderizar();
    SDL_RenderPresent(this->render);*/
}

Juego::~Juego(){}

void Juego::clean() {
      this->ventana->limpiar();
      this->corriendo = false;
}
