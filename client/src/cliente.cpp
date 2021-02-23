#include "../include/cliente.h"
#include "parser.h"
#include "../include/juego.h"
#include "../include/client_event_receiver.h"
#include "../include/client_event_sender.h"
#include "../include/manejador_eventos.h"
#include "../include/logInWindow.h"
#include "../include/audio.h"

#include <config.h>

#define MUSICA_FONDO SOUNDS_DIR THEME
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
    int screenHeightGame = parser.obtenerAltoPantallaJuego();
  //  int formatoPnatalla = parser.obtenerFormato(); para full screen capaz
  //pantalla de highscrore tamanio
  //tamanios de letras

    Audio audio;
    Musica musica(MUSICA_FONDO);
    musica.play(-1);
    LogInWindow logIn(screenWidthLogin, screenheightLogin, screenWidthGame);
    logIn.run();
    musica.stop();
    int idJugador = logIn.obtenerIdJugador();
    BlockingQueue<Comando *> events;
    ProtectedQueue<Actualizacion *> updates;
    Protocolo *protocolo = logIn.obtenerProtocolo();
    ClientEventSender clientEventSender(protocolo, events);



    Ventana ventana(nombre_juego, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidthGame,
                    screenHeightGame, /*SDL_WINDOW_FULLSCREEN*/0);
    Modelo modelo(ventana, idJugador, updates);

    ClientEventReceiver clientEventReceiver(protocolo, updates, modelo, idJugador);

    Juego juego(ventana, modelo);
    ManejadorEventos manejador(idJugador, events);

    try {
        clientEventSender.start();
        clientEventReceiver.start();
        while (!clientEventReceiver.recibi()) {
            std::cout << "";
        }
        juego.start();
        manejador.run();
        clientEventReceiver.cerrar();
        std::cerr << "sali del cerrar del receiver\n";
        clientEventReceiver.join();
        std::cerr << "sali del join del receiver\n";
        clientEventSender.cerrar();
        std::cerr << "sali del cerrar del sender\n";
        clientEventSender.join();
        std::cerr << "sali del join del sender\n";
        juego.cerrar();
        std::cerr << "sali del cerrar del juego\n";
        juego.join();
        std::cerr << "sali del join del juego\n";
    } catch (...) {
        std::cout << "ESTMAOS EN CATCH ";
        this->corriendo = false;

        juego.cerrar();
        clientEventSender.cerrar();

        clientEventReceiver.cerrar();

        clientEventSender.join();

        clientEventReceiver.join();
        juego.join();

    }

    //  ventana.cerrar();
    //  exit(1);

}
