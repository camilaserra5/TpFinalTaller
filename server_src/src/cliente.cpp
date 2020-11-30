#include "../include/cliente.h"
#include <mutex>


Cliente::Cliente(const std::queue<SDL_Event>& cola_eventos):
    cola_eventos(cola_eventos){}

Cliente::~Cliente(){}

void Cliente::run(){
    SDL_Event evento;
    std::mutex m;
    std::lock_guard<std::mutex> l(m);
    this->cola_eventos.push(evento);
}
