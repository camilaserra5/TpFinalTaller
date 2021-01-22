#include "../include/juego.h"
#define EXITO 0


Juego::Juego(const std::string& titulo, int ancho, int alto, bool fullscreen, int idJugador) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == EXITO) {
      /*
        this->ventana = SDL_CreateWindow(titulo, xpos, ypos, ancho, alto, flags);
        this->render = SDL_CreateRenderer(this->ventana, -1, 0);
        SDL_SetRenderDrawColor(this->render, 157, 97, 70, 255);
        SDL_RenderClear(this->render);*/

        this->ventana =  new Ventana(titulo, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ancho, alto, flags);
        this->modelo = new Modelo(this->ventana, idJugador);
        modelo->inicializar(); // recibiria el yaml
        this->corriendo = true;
    } else {
        this->corriendo = false;
    }
    this->texturaInferior = new Textura("../../client/resources/images/ParteInferior.png", this->ventana->obtener_render());

    //ObjetoJuego *enemigo = new ObjetoJuego("../../client/resources/images/Guard.png", this->ventana->obtener_render(),  /*50, 50,*/0, 0, 78, 78/*100,100*/);
    //this->objetos.push_back(enemigo);
}

void Juego::run(){
    this->clean();
    this->renderizar();
    this->actualizar();

}
void Juego::actualizar() {
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

void Juego::clean() {
      this->ventana->limpiar();
      this->corriendo = false;
}
