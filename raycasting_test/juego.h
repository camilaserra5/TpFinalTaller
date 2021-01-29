#ifndef JUEGO_H
#define JUEGO_H
#include "rayo.h"

#include "map.h"
#include "thread.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../client/include/textura.h"
#include "../client/include/ventana.h"
#include "blocking_queue.h"
#include "comandos/comando.h"
#include "../client/include/modelo.h"
#include <list>
#include <string>

#define ANCHO_CANVAS 640
#define ALTURA_CANVAS 400

class Juego : public Thread {
private:
    bool corriendo;
    Ventana *ventana;
    Textura *texturaInferior;
    Modelo *modelo;
    Jugador& jugador;

public:
    Juego(const std::string &titulo, int ancho, int alto, bool fullscreen, int idJugador,Jugador& jugador);

    ~Juego();

    //void inicializar(const std::string& titulo, int xpos, int ypos, int ancho, int alto, bool fullscreen);

    bool estaCorriendo() { return corriendo; }

//    void handleEvents(int id, BlockingQueue<Comando*>& eventos);
    void run() override;

    void actualizar(/*temporal int idArma*/);

    void renderizar();

    void clean();

    void raycasting(Map& mapaa, Jugador& jugador);
};

#endif /*JUEGO_H*/
