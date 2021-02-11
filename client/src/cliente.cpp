#include "../include/cliente.h"
#include "parser.h"
#include <iostream>
#include "../include/juego.h"
#include "blocking_queue.h"
#include "../include/client_event_receiver.h"
#include "../include/client_event_sender.h"
#include "../include/manejador_eventos.h"
#include <string>
#include "../include/logInWindow.h"

#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL.h>
#include "../include/musica.h"
#include "../include/audio.h"
#include "../include/highscoreWindow.h"
#define ARCHIVO_DE_CONFIGURACION "configClient.yaml"
#define MUSICA_FONDO "../../client/resources/sonidos/musiquita.wav"

Cliente::Cliente(const char *host, const char *server_port) : socket(), corriendo(true) {
    //  this->socket.conectar(host, server_port);
}

Cliente::~Cliente() {}

void Cliente::run() {
    std::string nombre_juego("Wolfstein");
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        printf("Failed to init SDL\n");
        exit(1);
    }
    if (TTF_Init() == -1) {
        printf("Failed to init TTF\n");
        exit(1);
    }
    Parser parser(ARCHIVO_DE_CONFIGURACION);
    int screenWidthLogin = parser.obtenerAnchoPantallaLogin();
    int screenheightLogin = parser.obtenerAltoPantallaLogin();

    LogInWindow logIn(screenWidthLogin,screenheightLogin);
    logIn.run();
    int idJugador = logIn.obtenerIdJugador();
    BlockingQueue<Comando *> events;
    ProtectedQueue<Actualizacion *> updates;
    Protocolo *protocolo = logIn.obtenerProtocolo();
    ClientEventSender clientEventSender(protocolo, events);

    //  Audio audio;
    //  Musica ambient_music = Musica(MUSICA_FONDO);
    //ambient_music.play(-1);

    Ventana ventana(nombre_juego, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, /*SDL_WINDOW_FULLSCREEN*/0);
    Modelo modelo(ventana, idJugador,updates);

    ClientEventReceiver clientEventReceiver(protocolo, updates, modelo, idJugador);

    Juego juego(ventana, modelo);
    ManejadorEventos manejador(idJugador, events);//no lanzar hilo

    try {
        clientEventSender.start();
        clientEventReceiver.start();
        while (!clientEventReceiver.recibi()){
            std::cout << "";
        }
        std::cout << "recibii main\n";
        juego.start();
        manejador.start();
        while (this->corriendo) {
            if (!manejador.esta_vivo()/*tiene que bloquearse*/) {
                std::chrono::milliseconds duration(700000);
                std::this_thread::sleep_for(duration);
                juego.join();
                juego.cerrar();
            }
            // se manejan eventos;
        }
    } catch (...) {
        std::cout << "error";
        this->corriendo = false;
        manejador.join();
        clientEventSender.join();
        clientEventReceiver.join();
        juego.join();
    }
    //  juego->join();
}
