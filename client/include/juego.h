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

class Juego : public Thread {
private:
    bool corriendo;
    Ventana *ventana;
    Textura *texturaInferior;
    Modelo *modelo;

public:
    Juego(const std::string &titulo, int ancho, int alto, bool fullscreen, int idJugador);

    ~Juego();

    bool estaCorriendo() { return corriendo; }

//    void handleEvents(int id, BlockingQueue<Comando*>& eventos);
    void run() override;

    void actualizar(/*temporal int idArma*/);

    void renderizar();

    void clean();
};

#endif /*JUEGO_H*/
