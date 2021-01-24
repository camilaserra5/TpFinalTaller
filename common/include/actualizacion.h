#ifndef ACTUALIZACION_H
#define ACTUALIZACION_H

#include "estadoJuego.h"
#include <list>
#include "iserializable.h"

class Actualizacion : public ISerializable {
public:
    Actualizacion(EstadoJuego &estadoJuego/*,std::list<EntidadPosicionable*> objetos*/) :
            estadoJuego(estadoJuego) {}
    /*objetos(objetos){
      //quizas se guarda la informacion de los rayos para dinujar, tipo un vector de alturas
      //y los jugadores que estan en su FOV junto con los items
    }*/
    std::stringstream serializar() override{
      std::stringstream info;
      return info;
    }
    void deserializar() override {}

private:
    EstadoJuego &estadoJuego;
    std::list<Item*> items;
    std::list<Jugador*> jugadores;
    int puntaje_actual;
    int vida_actual;
};

#endif
