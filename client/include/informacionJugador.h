#ifndef _INFORMACION_JUGADOR_H
#define _INFORMACION_JUGADOR_H

#include "label.h"
#include "fonts.h"
#include "textura.h"

class InfoJugador {
public:
    /*
      * creara la clase infoJugador dejandola valida para uso
      * el render debe ser distinto de null
    */
    InfoJugador(SDL_Renderer *render, int vida, int nivel, int puntaje,
                int cantVidas, int balas);

    /*
      * liberara la clase infoJugador con sus recursos
    */
    ~InfoJugador();

    /*
      * actualiza los datos del juagdor a mostrar
    */
    void actualizarDatosJugador(int vida, int nivel, int puntaje, int cantVidas,
                                int balas);

    /*
      * renderiza la informacion del jugador
    */
    void renderizar();

    /*
      * devuelve el puntaje del juagdor
    */
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
