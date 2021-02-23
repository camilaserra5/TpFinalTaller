#ifndef _VENTANA_H
#define _VENTANA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "textura.h"

#define ANCHO_CANVAS 800
#define ALTURA_CANVAS 600

class Ventana {
public:
    /*
      * creara la ventana dejandola valida para uso
      * sus parametros deben ser validos
    */
    Ventana(const std::string &titulo, int x, int y, int ancho, int alto, int flags);

    /*
      * liberara la ventana con sus recursos
    */
    ~Ventana();

    /*
      * devuelve el render
    */
    SDL_Renderer *obtener_render();

    /*
      * actualiza la ventana
    */
    void actualizar();

    /*
      * limbia la ventana
    */
    void limpiar();

    /*
      * cierra la ventana
    */
    void cerrar();

private:
    SDL_Window *ventana;
    SDL_Renderer *render;
    int x;
    int y;
    bool cerrada = false;
};

#endif
