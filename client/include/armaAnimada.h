#ifndef _ARMA_ANIMADA_H
#define _ARMA_ANIMADA_H

#include "sprite.h"
#include "animacion.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

class ArmaAnimada{
    public:
          ArmaAnimada(SDL_Renderer* render);
          ~ArmaAnimada();
<<<<<<< HEAD
          void renderizar(bool& disparando);
=======
          void renderizar(bool disparando);
>>>>>>> 4269baa58c62fc635ff9f9b799dfc21193b8979b
          void actualizar(int idArma);

    private:
          std::map<int, Sprite> sprites;
          std::map<int, Animacion> animaciones;
          int armaActual;
};

#endif
