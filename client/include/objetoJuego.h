#ifndef OBJETOJUEGO_H
#define OBJETOJUEGO_H

#include "sprite.h"
#include "posicion.h"
#include "objetoDibujable.h"

class ObjetoJuego : public ObjetoDibujable {
private:
    Posicion posicion;
    Sprite sprite;
    int distanciaParcialAJugador;

public:
    /*
      * creara al objeto juego dejandolo valido para uso
    */
    ObjetoJuego(Sprite sprite);
    /*
      * liberara el obejeto juego con sus recursos
    */
    ~ObjetoJuego();
    /*
      * renderiza al sprite
    */
    void renderizar();
    /*
      * settea el estado del objeto juego
    */
    void settear_estado(int posx, int posy);
    /*
      * devuelve la posicon del objeto
    */
    Posicion &getPosicion();
    /*
      * renderiza por columna al sprite
    */
    void renderizarColumna(SDL_Rect &dimension, SDL_Rect &dest) override;
    /*
      * reescala el sprite en ancho y largo
    */
    void reescalar(int escalarw, int escalarh);
    /*
      * devuelve el ancho del sprite
    */   
    int obtenerAnchura();
};

#endif //OBJETOJUEGO_H
