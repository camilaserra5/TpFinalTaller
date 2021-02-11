#ifndef _LOGIN_H
#define _LOGIN_H

#include <SDL2/SDL.h>
#include "../include/fonts.h"
#include "socket.h"
#include "protocolo.h"


class LogInWindow {

public:
    LogInWindow(int screnWidth, int screenHeight);

    void run();

    ~LogInWindow();

    Protocolo *obtenerProtocolo() {
        return this->protocolo;
    }

    uint32_t obtenerIdJugador() {
        return this->idCliente;
    }

private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    Fonts fonts;
    Socket socket;//hay qeu sacarlo
    Protocolo *protocolo;
    uint32_t idCliente;
    int screenWidth;
    int screenHeight;

    void mostrarMenuPartidas(SDL_Renderer *renderer, Fonts fonts,
                             std::vector<std::string> partidas, int &gameNumber);

    void start(SDL_Renderer *renderer, Fonts fonts);

    void connect(SDL_Renderer *renderer, Fonts fonts, std::string &ip, std::string &port, std::string &message);

    void pantallaError(SDL_Renderer *renderer, Fonts fonts, std::string &error);

    void pantallaEsperando(SDL_Renderer *renderer, Fonts fonts, Protocolo *protocolo);

    void unirseAPartida(SDL_Renderer *renderer, Fonts fonts, std::string &nombre, std::string &playerName);

    void crearPartida(SDL_Renderer *renderer, Fonts fonts, std::string &param, int &option,
                      std::string &gameName, std::string &numberPlayers,
                      std::string &mapFile, std::string &playerName);


};

#endif
