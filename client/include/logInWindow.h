#ifndef _CLIENT_H
#define _CLIENT_H

#include <SDL2/SDL.h>
#include "../include/fonts.h"
#include "socket.h"
#include "protocolo.h"

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

class LogInWindow {

public:
    LogInWindow();

    void run();

    ~LogInWindow();

    Protocolo* obtenerProtocolo(){
        return this->protocolo;
    }

    int obtenerIdJugador(){
        return this->idJugador;
    }

private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    Fonts fonts;
    Socket socket;
    Protocolo* protocolo;
    int idJugador;

};

#endif
