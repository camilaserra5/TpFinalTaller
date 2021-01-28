#include "../include/cliente.h"
//#include "socket.h"
#include <iostream>
#include "../include/juego.h"
#include "blocking_queue.h"
#include "../include/client_event_receiver.h"
#include "../include/client_event_sender.h"
#include "../include/manejador_eventos.h"
#include <string>

Cliente::Cliente(const char *host, const char *server_port) : socket() {
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
    ManejadorEventos manejador(idJugador, events);

    try {
        //  juego->inicializar(nombre_juego, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
        while (juego->estaCorriendo()) {

            // clientEventSender.enviarEventos
            if (!manejador.esta_vivo()) {
                juego->clean();
                SDL_Quit();
                exit(1);
            }
            juego->run();
            manejador.start(); // se manejan eventos;
            std::chrono::milliseconds duration(1000);
            std::this_thread::sleep_for(duration);

        }
        juego->clean();
    } catch (...) {
        std::cout << "error";
    }
    //  juego->join();
    manejador.join();
}
