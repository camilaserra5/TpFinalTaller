#ifndef JUEGO_H
#define JUEGO_H

#include "objetoJuego.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "textura.h"
#include <list>

class Juego {
private:
    std::list<ObjetoJuego *> objetos;
    bool corriendo;
    SDL_Window *ventana;
    SDL_Renderer *render;
    Textura *texturaInferior;
public:
    Juego() {}

    ~Juego() {}

    void inicializar(const char *titulo, int xpos, int ypos, int ancho, int alto, bool fullscreen);

    bool estaCorriendo() { return corriendo; }

    void handleEvents();

    void actualizar();

    void renderizar();

    void clean();

    void raycasting();
};

#endif /*JUEGO_H*/
