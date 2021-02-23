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
    if (!this->cerrada) {
        if (this->render != nullptr) {
            SDL_DestroyRenderer(this->render);
            this->render = nullptr;
        }
        if (this->ventana != nullptr) {
            SDL_DestroyWindow(this->ventana);
            this->ventana = nullptr;
        }
    }
    this->cerrada = true;
}

SDL_Renderer *Ventana::obtener_render() {
    return this->render;
}

void Ventana::actualizar() {
    if (this->render != nullptr) SDL_RenderPresent(this->render);
}

void Ventana::limpiar() {
    if (this->render != nullptr) SDL_RenderClear(this->render);
}
