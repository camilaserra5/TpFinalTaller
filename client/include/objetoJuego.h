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
    ObjetoJuego(Sprite sprite);

    ~ObjetoJuego();

    void renderizar();

    void settear_estado(int posx, int posy);

    Posicion &getPosicion();

    void renderizarColumna(SDL_Rect &dimension, SDL_Rect &dest) override;

    void reescalar(int escalarw, int escalarh);

    int obtenerAnchura();
};

#endif //OBJETOJUEGO_H
