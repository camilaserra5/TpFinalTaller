#ifndef _HIGHSCHOR_H
#define _HIGHSCHOR_H

#include <SDL2/SDL.h>
#include "../include/fonts.h"
#include "socket.h"
#include "protocolo.h"
#include "ventana.h"
#include <map>
#include "player.h"
#include "enemigo.h"
#include <vector>

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

class HighscoreWindow {

public:
    HighscoreWindow(Ventana& ventana);

    void renderizar();

    void show_highscores(SDL_Renderer *renderer, Fonts fonts);

    void settearGanadores(std::vector<int>& ganadores,Player *jugador, std::map<int, Enemigo *> &enemigos);

    ~HighscoreWindow();

private:
    SDL_Renderer *renderer;
    Ventana& ventana;
    Fonts fonts;
    std::map<int, int> ganadores;

};

#endif
