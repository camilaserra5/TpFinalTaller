#ifndef _TEXTO_H
#define _TEXTO_H

#include "textura.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#include "ventana.h"

class Texto{
    private:
          Ventana& ventana;
          Textura textura_texto;
          //TTF_Font* fuente;
          SDL_Color actualColor;
          std::string texto;
          SDL_Rect posicion;
    public:
            Texto(Ventana& ventana);
            ~Texto();
            void settearTexto(std::string texto);
            void settearPosicion(SDL_Rect posicion);
            void renderizar();

};

#endif
