#ifndef _INFORMACION_JUGADOR_H
#define _INFORMACION_JUGADOR_H

#include "label.h"
#include "fonts.h"
#include "textura.h"

class InfoJugador {
public:

    InfoJugador(SDL_Renderer *render, int vida, int nivel, int puntaje,
                int cantVidas, int balas);

    ~InfoJugador();

    void actualizarDatosJugador(int vida, int nivel, int puntaje, int cantVidas,
                                int balas);

    void renderizar();

    int getPuntaje();

private:
    Label *vida;
    Label *nivel;
    Label *puntaje;
    Label *cantVidas;
    Label *balas;
    Textura *texturaInferior;

};

#endif
