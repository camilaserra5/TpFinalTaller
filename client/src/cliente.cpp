#include "../include/cliente.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../include/juego.h"
#include "blocking_queue.h"
#include "protected_queue.h"
#include "../include/client_event_receiver.h"
#include "../include/client_event_sender.h"

#define BUFFER_TAM 50
#define ERROR -1

#define SOCKET_CERRADO 0

Cliente::Cliente(const char *host, const char *server_port) : socket() {
    this->socket.conectar(host, server_port);
}

void Cliente::correr() {
    //BlockingQueue<Comando *> event_queue;
    //ProtectedQueue<Comando *> updates_queue;

    ClientEventSender sender(this->socket);
    sender.start();

    ClientEventReceiver receiver(this->socket);
    receiver.start();

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

    sender.cerrar();
    receiver.cerrar();

    sender.join();
    receiver.join();
}

Cliente::~Cliente() {}
