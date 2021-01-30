#ifndef _ANIMACION_H
#define _ANIMACION_H

//nframes = SDL_GetTicks()/velocidad % cantFrames

#include "textura.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

class Animacion{
    private:
          Textura* textura;
          std::vector<SDL_Rect> frames;
          int frame_h;
          int frame_w;

    public:
        Animacion(SDL_Renderer* render,
                               const char* rutaimg,
                               int frames,
                               int frame_h,
                               int frame_w,
                              int fila){

          SDL_Rect rect = {0, fila*frame_h, frame_h, frame_w};
          for (int i = 0; i < frames; i++) {
              this->frames.push_back(rect);
              rect.x += frame_w;
          }
          this->textura = new Textura(rutaimg, render);
          this->frame_h = frame_h;
          this->frame_w = frame_w;
       }
        ~Animacion(){}

    void renderizar(int posx, int posy){
        static float counter;
        if (int(counter) > frames.size())
            counter = 0;
        SDL_Rect r = {posx, posy, this->frame_h*2, this->frame_w*2}; // Donde se renderiza
        textura->renderizar(&frames[counter], r);
        counter = counter + 0.065;

    }
};

#endif
