#ifndef _ANIMACION_H
#define _ANIMACION_H

//nframes = SDL_GetTicks()/velocidad % cantFrames

#include "textura.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <iostream>

class Animacion {
private:
    Textura textura;
    std::vector<SDL_Rect> frames;
    int frame_h;
    int frame_w;
    int frameActual;
    int contador;
    int velocidad;

public:
    /*
      * crea la animacion dejandola valida para uso
    */
    Animacion(SDL_Renderer *render,
              const char *rutaimg,
              int frames,
              int frame_h,
              int frame_w,
              int fila, int columna);
    /*
      *
    */  
    ~Animacion();
    /*
      * realiza el renderizado del sprite completo en la posx e y
    */
    void renderizar(int posx, int posy, int angulo, SDL_Point *centro);
    /*
      * realiza el renderizado por comuna del sprite
    */
    void renderizarColumna(SDL_Rect &dimension, SDL_Rect dest);
};

#endif
