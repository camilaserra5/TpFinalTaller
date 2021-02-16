#ifndef _ARMA_ANIMADA_H
#define _ARMA_ANIMADA_H

#include "sprite.h"
#include "animacion.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

class ArmaAnimada {
public:
    ArmaAnimada(SDL_Renderer *render);

    ~ArmaAnimada();

    void renderizar();

    void actualizar(int idArma, bool estado);

private:
    std::map<int, Sprite> sprites;
    std::map<int, Animacion> animaciones;
    int armaActual;
    int contador;
    bool atacando;
};

#endif
