#ifndef JUEGO_H
#define JUEGO_H
#define ANCHO_CANVAS 800
#define ALTURA_CANVAS 320

#include "objetoJuego.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "textura.h"
#include "jugador.h"
#include "map.h"
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

    void raycasting(Map &mapa, Jugador &jugador);
};

#endif /*JUEGO_H*/
