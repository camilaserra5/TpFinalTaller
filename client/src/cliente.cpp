#include "../include/cliente.h"
#include "parser.h"
#include "../include/juego.h"
#include "../include/client_event_receiver.h"
#include "../include/client_event_sender.h"
#include "../include/manejador_eventos.h"
#include "../include/logInWindow.h"

#include <config.h>

#define MUSICA_FONDO SOUNDS_DIR MUSIQUITA
#define ERROR -1

Cliente::Cliente(std::string configFile) : socket(),
                                           corriendo(true) {
    if (!configFile.empty()) {
        this->configFile = configFile;
    }
}

Cliente::~Cliente() {}

void Cliente::run() {
    std::string nombre_juego("Wolfestein");
    if (SDL_Init(SDL_INIT_EVERYTHING) == ERROR) {
        printf("Failed to init SDL\n");
        exit(1);
    }
    if (TTF_Init() == ERROR) {
        printf("Failed to init TTF\n");
        exit(1);
    }
    Parser parser(configFile);
    int screenWidthLogin = parser.obtenerAnchoPantallaLogin();
    int screenheightLogin = parser.obtenerAltoPantallaLogin();
    int screenWidthGame = parser.obtenerAnchoPantallaJuego();
  //  int screenHeightGame = parser.obtenerAltoPantallaJuego();
    LogInWindow logIn(screenWidthLogin, screenheightLogin, screenWidthGame);
    logIn.run();
    int idJugador = logIn.obtenerIdJugador();
    BlockingQueue<Comando *> events;
    ProtectedQueue<Actualizacion *> updates;
    Protocolo *protocolo = logIn.obtenerProtocolo();
    ClientEventSender clientEventSender(protocolo, events);

    //  Audio audio;
    //  Musica ambient_music = Musica(MUSICA_FONDO);
    //  ambient_music.play(-1);

    Ventana ventana(nombre_juego, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidthGame, 600, /*SDL_WINDOW_FULLSCREEN*/0);
    Modelo modelo(ventana, idJugador, updates);

    ClientEventReceiver clientEventReceiver(protocolo, updates, modelo, idJugador);

    Juego juego(ventana, modelo);
    ManejadorEventos manejador(idJugador, events);//no lanzar hilo

    try {
        clientEventSender.start();
        clientEventReceiver.start();
        while (!clientEventReceiver.recibi()) {
            std::cout << "";
        }
        std::cout << "recibii main\n";
        juego.start();
        manejador.run();
        juego.cerrar();
        clientEventSender.cerrar();
        std::cerr << "sali del cerrar del sender\n";

        clientEventReceiver.cerrar();
        clientEventSender.join();
        clientEventReceiver.join();
        juego.join();
    } catch (...) {
        std::cout << "error";
        this->corriendo = false;

        juego.cerrar();
        std::cerr << "sali del cerrar del juego\n";
        clientEventSender.cerrar();

        clientEventReceiver.cerrar();
        std::cerr << "sali del cerrar del receiver\n";

        clientEventSender.join();
        std::cerr << "sali del join del sender\n";

        clientEventReceiver.join();
        std::cerr << "sali del join del receiver\n";
        juego.join();
        std::cerr << "sali del join del juego\n";


    }

}
