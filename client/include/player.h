#ifndef _PLAYER_H
#define _PLAYER_H

#include "informacionJugador.h"
#include "armaAnimada.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Player {
public:
    Player(const char *rutaimg, SDL_Renderer *render, int& id);

    ~Player();

    void actualizacion(int& posx, int& posy, int& vida, int& angulo, int& arma);

    void renderizar();

    void settear_estado(int& posx, int& posy, int& vida, int& angulo, int& arma);

    void dejarDeDisparar(){
        this->disparando = false;
    }

private:
    int posx;
    int posy;
    int vida;
    int nivel;
    int puntaje;
    int angulo;
    int id;
    ArmaAnimada arma;
    InfoJugador infoJugador;
    int cantVidas;
    bool disparando;
};

#endif
