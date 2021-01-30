#include "../include/juego.h"

#define EXITO 0

#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL.h>

#define LOWER_TEXTURE_ROOT "../../client/resources/images/ParteInferior.png"

Juego::Juego(const std::string &titulo, int ancho, int alto, bool fullscreen, int idJugador) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == EXITO) {


        if (TTF_Init() == -1) {
            printf("Failed to init TTF\n");
            exit(1);
        }

        this->ventana = new Ventana(titulo, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ancho, alto, flags);
        this->modelo = new Modelo(this->ventana, idJugador);
        modelo->inicializar();
        this->texturaInferior = new Textura(LOWER_TEXTURE_ROOT,
                                            this->ventana->obtener_render());
        this->corriendo = true;
    } else {
        this->corriendo = false;
    }
}

void Juego::run() {
    while(this->corriendo){
        try {
              this->clean();
              this->renderizar();
              this->actualizar(/*1*/);
        } catch (...) {
            this->corriendo = false;
        }
    }

}

void Juego::actualizar(/*temporal int idArma*/) {
    this->ventana->actualizar();
}

void Juego::renderizar() {
    this->ventana->renderizar(this->texturaInferior);
    this->modelo->renderizar();

}

Juego::~Juego() {}

void Juego::cerrar(){
    this->corriendo = false;
    this->ventana->cerrar();
};
void Juego::clean() {
    this->ventana->limpiar();
  //  this->corriendo = false;
}
