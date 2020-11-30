#include "../include/cliente.h"


Cliente::Cliente(const std::queue<STD_Event>& cola_eventos):
    cola_eventos(cola_eventos){}

Cliente::~Cliente(){}

Cliente::run(){
    SDL_Event evento;
    this->cola_eventos.push_back(evento);
}
