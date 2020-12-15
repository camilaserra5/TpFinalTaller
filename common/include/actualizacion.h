#ifndef ACTUALIZACION_H
#define ACTUALIZACION_H

#include "estadoJuego.h"

class Actualizacion {
public:
    Actualizacion(EstadoJuego &estadoJuego,std::list<EntidadPosicionable*> objetos):
            estadoJuego(estadoJuego),
            objetos(objetos){
              //quizas se guarda la informacion de los rayos para dinujar, tipo un vector de alturas
              //y los jugadores que estan en su FOV junto con los items
            }

private:
    EstadoJuego &estadoJuego;
    std::list<EntidadPosicionable*> objetos;
};

#endif
