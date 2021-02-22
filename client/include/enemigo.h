#ifndef _ENEMIGO_H
#define _ENEMIGO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "animacion.h"
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "posicion.h"
#include "objetoDibujable.h"

class Enemigo : public ObjetoDibujable {
public:
    /*
      * creara al enemigo dejandolo valido para uso
      * el render debe ser distinto de null
    */
    Enemigo(SDL_Renderer *render, int idArmaJugador);
    /*
      * elimina la clase enemigo junto a sus recursos
    */
    ~Enemigo();
    /*
      * actualiza por primera vez al enemigo
    */
    void actualizar(int posx, int posy, int idArma, int anguloEnemigo,
                    int anguloJugador, int vida, bool disparando, int puntaje);
    /*
      * renderiza al enemigo de acuerdo al arma que tenga el juagdor
    */
    void renderizar();
    /*
      * verifica el estado del enemigo
    */
    void verificarEstado(Posicion &posicionNueva, int vida, bool disparando);
    /*
      * renderiza al enemigo de acuerdo al arma que tiene por columna
    */
    void renderizarColumna(SDL_Rect &dimension, SDL_Rect &dest) override;
    /*
      * devuelve la posicicion del enemigo
    */
    Posicion &getPosicion();
    /*
      * devuelve el puntaje del enemigo
    */
    int getPuntaje() {
        return this->puntaje;
    }
    /*
      * actualiza el arma del jugador
    */
    void actualizarArma(int idArma) {
        this->idArma = idArma;
    }
    /*
      * devuelve el ancho del sprite
    */
    int obtenerAnchura();
    /*
      * actualiza la posicon de enemigo
    */
    void actualizarPosicion(int posX, int posY, float angulo);
    /*
      * actualiza la vida del enemigo
    */  
    void actualizarVida(int vida);

private:
    int idArma;
    int anguloJugador;
    int estado;
    int distanciaParcialAJugador;
    Posicion posicion;
    std::multimap<int, std::vector<Animacion>> enemigos;
    int puntaje;
};

#endif
