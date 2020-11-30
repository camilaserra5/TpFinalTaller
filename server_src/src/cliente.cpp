#include "../include/cliente.h"


Cliente::Cliente(const std::queue<SDL_Event>& cola_eventos):
    cola_eventos(cola_eventos){}

Cliente::~Cliente(){}

void Cliente::run(){
    SDL_Event evento;
    this->cola_eventos.push(evento);
}
