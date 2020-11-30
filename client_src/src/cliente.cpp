#include "../include/cliente.h"
#include <mutex>


Cliente::Cliente(ProtectedQueue& cola_eventos):
    cola_eventos(cola_eventos){}

Cliente::~Cliente(){}

void Cliente::run(){
    SDL_Event evento;
    this->cola_eventos.aniadir_evento(evento);
}
