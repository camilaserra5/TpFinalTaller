#ifndef _SPRITE_H
#define _SPRITE_H


#include "textura.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite {
private:
    Textura textura;
    SDL_Rect infoSprite;
    SDL_Rect destino;

public:
    /*
      * creara la clase sprite dejandola valida para uso
      * sus parametros deben estar inicializados
    */
    Sprite(SDL_Renderer *render, const char *rutaimg, int x, int y, int h, int w);
    /*
      * liberara a la clase con sus recursos
    */
    ~Sprite() {}
    /*
      * renderiza al sprite
    */
    void renderizar(int x, int y, int angulo, SDL_Point *centro);
    /*
      * reescala el sprite en ancho y largo
    */
    void reescalar(int escalarw, int escalarh);
    /*
      * settea el frame
    */
    void setFrame(int frame) {
        this->infoSprite.x = frame * this->infoSprite.w;
    }
    /*
      * reenderiza por comlumna el sprite
    */  
    void renderizarColumna(SDL_Rect dimension, SDL_Rect &dest);

};

#endif
