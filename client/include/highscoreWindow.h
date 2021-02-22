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
    /*
      * creara la clase highscorewindow dejandola valida para uso
      * la venta ya debe estar incializada
    */
    HighscoreWindow(Ventana &ventana);

    /*
      * renderiza la ventana de puntaje
    */
    void renderizar();

    /*
      * muesta los puntos mas altos
    */
    void show_highscores(SDL_Renderer *renderer, Fonts fonts);

    /*
      * settea los ganadores en orden de mayor puntaje a menor puntaje
    */
    void settearGanadores(Ranking &ranking);

    /*
      * liberara la clase junto a sus recursos
    */
    ~HighscoreWindow();

private:
    SDL_Renderer *renderer;
    Ventana &ventana;
    Fonts fonts;
    Ranking *ranking;

};

#endif
