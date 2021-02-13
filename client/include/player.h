#ifndef _PLAYER_H
#define _PLAYER_H

#include "informacionJugador.h"
#include "armaAnimada.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "posicion.h"

class Player {
public:
    Player(const char *rutaimg, SDL_Renderer *render, int id);

    ~Player();

    void actualizar(int posx, int posy, int vida, float angulo, int idArma,
                    bool disparando, int puntaje, int cantVidas, int balas);

    void renderizar();

    void dejarDeDisparar() {
        this->disparando = false;
    }
    void actualizarArma(int idArma){
        this->arma.actualizar(idArma);
    }

    Posicion &getPosicion();

    float getAnguloDeVista();

    int getPuntaje();

    int getId();

private:
    Posicion posicion;
    int id;
    ArmaAnimada arma;
    InfoJugador infoJugador;
    bool disparando;
};

#endif
