#ifndef JUEGO_H
#define JUEGO_H

#include "objetoJuego.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "textura.h"
#include "ventana.h"
#include <list>
#include <string>

class Juego {
private:
    std::list<ObjetoJuego *> objetos;
    bool corriendo;
    Ventana* ventana;
    Textura *texturaInferior;
public:
    Juego(const std::string& titulo, int xpos, int ypos, int ancho, int alto, bool fullscreen);

    ~Juego() {}

    //void inicializar(const std::string& titulo, int xpos, int ypos, int ancho, int alto, bool fullscreen);

    bool estaCorriendo() { return corriendo; }

    void handleEvents();

    void actualizar();

    void renderizar();

    void clean();
};

#endif /*JUEGO_H*/
