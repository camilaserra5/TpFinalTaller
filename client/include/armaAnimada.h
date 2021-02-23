#ifndef _ARMA_ANIMADA_H
#define _ARMA_ANIMADA_H

#include "sprite.h"
#include "animacion.h"
#include "musica.h"
#include "audio.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

class ArmaAnimada {
public:
    /*
      * crea al arma animada dejandola valida para uno
    */
    ArmaAnimada(SDL_Renderer *render);

    /*
      * libera la clase arma Nimada con todos sus recursos
    */
    ~ArmaAnimada();

    /*
      * se encarga de renderizar El arma actual
    */
    void renderizar();

    /*
      * actualizar el arma con el cual se renderiza
    */
    void actualizar(int idArma, bool estado);

private:
    std::map<int, Sprite> sprites;
    std::map<int, Animacion> animaciones;
    std::map<int, Musica*> sonidos;
    int armaActual;
    int contador;
    bool atacando;
};

#endif
