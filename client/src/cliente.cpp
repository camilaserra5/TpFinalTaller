#include "../include/cliente.h"
//#include "socket.h"
#include <iostream>
#include "../include/juego.h"

Cliente::Cliente(ProtectedQueue<Comando *> &cola_eventos, const char *host, const char *server_port) :
        cola_eventos(cola_eventos) {}

Cliente::~Cliente() {}

void Cliente::run() {
    //Comando* evento;
    //ACA IRIA UN HANDLER EVENT
    //this->cola_eventos.aniadir_comando(evento);
    //SE VAN AÑADIENDO, SE ENVIAN Y SE ACTUALIZA.
    //LO QUE RECIBA DE LA ACTUALIZACION HAY QUE DIBUJARLO.
    Juego *juego = new Juego();
    try {
        juego->inicializar("Wolfstein", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
        while (juego->estaCorriendo()) {
            juego->handleEvents();
            juego->actualizar();
            juego->renderizar();
        }
        juego->clean();
    } catch (...) {
        std::cout << "error";
    }
}
