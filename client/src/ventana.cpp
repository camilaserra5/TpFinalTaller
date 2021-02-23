#include "../include/ventana.h"
#include <iostream>

Ventana::Ventana(const std::string &titulo, int x, int y, int ancho, int alto, int flags) {
    this->ventana = SDL_CreateWindow(titulo.c_str(), x, y, ancho, alto, flags);
    this->render = SDL_CreateRenderer(this->ventana, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!this->ventana) {
        throw std::runtime_error("Error: No se creo la ventana");
    }
    SDL_SetRenderDrawColor(this->render, 60, 60, 60, 10);
    SDL_RenderClear(this->render);
}

Ventana::~Ventana() {
}

void Ventana::cerrar() {
  std::cerr << "estro a entrar ventana\n";
//  std::cerr << "this->ventana: " << this->ventana << std::endl;
  if (this->render != NULL){
    SDL_DestroyRenderer(this->render);
    this->render = NULL;
  }
  if (this->ventana != NULL){
    SDL_DestroyWindow(this->ventana);
    this->ventana = NULL;
  }

}

SDL_Renderer *Ventana::obtener_render() {
    return this->render;
}

void Ventana::actualizar() {
    if (this->render != NULL) SDL_RenderPresent(this->render);
}

void Ventana::limpiar() {
    if (this->render != NULL) SDL_RenderClear(this->render);
}
