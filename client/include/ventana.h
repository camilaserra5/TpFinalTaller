#ifndef _VENTANA_H
#define _VENTANA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "textura.h"

class Ventana {
    public:
        Ventana(const std::string& titulo, int x, int y, int ancho, int alto, int flags);
        ~Ventana();
        SDL_Renderer* obtener_render();
        void renderizar(Textura* textura);
        void actualizar();
        void limpiar();

    private:
      SDL_Window* ventana;
      SDL_Renderer *render;
      int x;
      int y;
};

#endif
