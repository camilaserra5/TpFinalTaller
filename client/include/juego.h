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
#include <map>
#include <string>
#include "rayo.h"
#include "map.h"


class Juego : public Thread {
private:
    bool corriendo;
    Ventana &ventana;
    Modelo &modelo;
    bool inicialice = false;
    std::map<int, Textura *> texturas;

public:
    /*
      * creara la clase juego dejandola valida para uso
      * tanto como la ventana y el modelo ya deben estar inicializados
    */
    Juego(Ventana &ventana, Modelo &modelo);
    /*
      * liberara a la clase juego con sus recursos
    */
    ~Juego();
    /*
      * devuelve si el juego esta corriendo o no
    */
    bool estaCorriendo() { return corriendo; }
    /*
      * es donde se ejecuta el loop game
    */
    void run() override;
    /*
      * actualiza la ventana que ve el juagdor
    */
    void actualizar();
    /*
      * renderiza las correspondientes entidades
    */
    void renderizar();
    /*
      * limpia la ventana que ve el juagdor
    */
    void clean();
    /*
      * cerrara el juego
    */
    void cerrar();
    /*
      * realiza el algortimo de raycasting
    */
    void raycasting(Map &mapa, Player &jugador);
    /*
      * realiza el loop de eventos
    */
    void eventos();
    /*
      * verifica el tipo de pared y  devuelve la textura correspondiente
    */
    Textura *verificarTextura(SDL_Renderer *render, int &tipoDePared);
    /*
      * renderiza la pared correspondiente con la determina textura
    */
    void renderizarPared(SDL_Renderer *render, Rayo &rayo, int &posCanvas, unsigned int &alturaParedProyectada);
};

#endif /*JUEGO_H*/
