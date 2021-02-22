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
    SDL_DestroyRenderer(this->render);
    SDL_DestroyWindow(this->ventana);
}

SDL_Renderer *Ventana::obtener_render() {
    return this->render;
}

void Ventana::actualizar() {
    SDL_RenderPresent(this->render);
}

void Ventana::limpiar() {
    SDL_RenderClear(this->render);
}
