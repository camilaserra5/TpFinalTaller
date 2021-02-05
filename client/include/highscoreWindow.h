#ifndef _HIGHSCHOR_H
#define _HIGHSCHOR_H

#include <SDL2/SDL.h>
#include "../include/fonts.h"
#include "socket.h"
#include "protocolo.h"

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

class HighscoreWindow {

public:
    HighscoreWindow();

    void run();

    ~HighscoreWindow();

private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    Fonts fonts;

};

#endif
