#ifndef JUEGO_H
#define JUEGO_H

#include "thread.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "textura.h"
#include "ventana.h"
#include "blocking_queue.h"
#include "comandos/comando.h"
#include "modelo.h"
#include <list>
#include <string>
#include "rayo.h"
#include "map.h"


class Juego : public Thread {
private:
    bool corriendo;
    Ventana& ventana;
    Textura *texturaInferior;
    Modelo& modelo;

public:
    Juego(Ventana& ventana, Modelo& modelo);

    ~Juego();

    bool estaCorriendo() { return corriendo; }

    void run() override;

    void actualizar();

    void renderizar();

    void clean();

    void cerrar();

    void raycasting(Map& mapaa, Player& jugador);

    void eventos();

    Textura* verificarTextura(SDL_Renderer* render,int& tipoDePared);

    void renderizarPared(SDL_Renderer* render,Rayo& rayo,int& posCanvas,unsigned int& alturaParedProyectada);
};

#endif /*JUEGO_H*/
