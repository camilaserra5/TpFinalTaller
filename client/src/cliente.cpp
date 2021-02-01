#include "../include/cliente.h"
//#include "socket.h"
#include <iostream>
#include "../include/juego.h"
#include "blocking_queue.h"
#include "../include/client_event_receiver.h"
#include "../include/client_event_sender.h"
#include "../include/manejador_eventos.h"
#include <string>

Cliente::Cliente(const char *host, const char *server_port) : socket(), corriendo(true) {
    //  this->socket.conectar(host, server_port);
}

Cliente::~Cliente() {}

void Cliente::run() {
    BlockingQueue<Comando *> events;
    //  ClientEventSender clientEventSender(socket, events);
    //clientEventSender.run();

    ProtectedQueue<Actualizacion *> updates;
    //ClientEventReceiver clientEventReceiver(socket, updates);
    //clientEventReceiver.run();

    //Comando* evento;
    //ACA IRIA UN HANDLER EVENT
    //this->cola_eventos.aniadir_comando(evento);
    //SE VAN AÑADIENDO, SE ENVIAN Y SE ACTUALIZA.
    //LO QUE RECIBA DE LA ACTUALIZACION HAY QUE DIBUJARLO.
    std::string nombre_juego("Wolfstein");
    int idJugador = 1111;
    Juego *juego = new Juego(nombre_juego, 800, 600, false, idJugador);
    ManejadorEventos* manejador = new ManejadorEventos(idJugador, events);

    try {
        //  juego->inicializar(nombre_juego, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
        juego->start();
        manejador->start();
        while (this->corriendo) {

            // clientEventSender.enviarEventos
             // hay error cuando se hace juego->start;
            if (!manejador->esta_vivo()) {
                juego->join(); //
                juego->cerrar();

            }
             // se manejan eventos;

        }
    } catch (...) {
        std::cout << "error";
        this->corriendo = false;
        manejador->join();
    }
    //  juego->join();
}
