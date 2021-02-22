#ifndef _PLAYER_H
#define _PLAYER_H

#include "informacionJugador.h"
#include "armaAnimada.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "posicion.h"

class Player {
public:
    /*
      * creara la clase player dejandola valida para uso
      * los parametros deben estar inicializados
    */
    Player(const char *rutaimg, SDL_Renderer *render, int id);

    /*
      * liberara al player con sus recursos
    */
    ~Player();

    /*
      * actualizara al juagdor con sus valores iniciales
    */
    void actualizar(int posx, int posy, int vida, float angulo, int idArma,
                    bool disparando, int puntaje, int cantVidas, int balas);

    /*
      * renderiza a los atributos del juagdor
    */
    void renderizar();

    /*
      * actualiza el arma del jugador
    */
    void actualizarArma(int idArma, bool estado) {
        this->arma.actualizar(idArma, estado);
    }

    /*
      * devuelve la posicion del juagdor
    */
    Posicion &getPosicion();

    /*
      * devuelve el angulo de vista
    */
    float getAnguloDeVista();

    /*
      * devuelve el puntaje del juagdor
    */
    int getPuntaje();

    /*
      * devuelve el id del juagdor
    */
    int getId();

    /*
      * actualiza los datos del juagdor que se le muestran al cliente
    */
    void actualizarDatosJugador(int vida, int cant_vidas, int puntaje, int balas);

private:
    Posicion posicion;
    int id;
    ArmaAnimada arma;
    InfoJugador infoJugador;
};

#endif
