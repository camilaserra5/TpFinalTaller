#ifndef _CLIENT_H
#define _CLIENT_H

#include <SDL2/SDL.h>
#include "../include/fonts.h"
#include "socket.h"

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

class Client {

public:
    Client();

    void run();

    ~Client();

private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    Fonts fonts;
    Socket socket;

};

#endif
