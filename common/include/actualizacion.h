#ifndef ACTUALIZACION_H
#define ACTUALIZACION_H

#include "estadoJuego.h"
#include <list>
#include "iserializable.h"

class Actualizacion : public ISerializable {
public:
    Actualizacion(EstadoJuego &estadoJuego/*,std::list<EntidadPosicionable*> objetos*/) :
            estadoJuego(estadoJuego) {
        estadoJuego.verificarJugadoresMuertos();//pasar a metodo actualizar en estadoJuego
    }

    /*objetos(objetos){
      //quizas se guarda la informacion de los rayos para dinujar, tipo un vector de alturas
      //y los jugadores que estan en su FOV junto con los items
    }*/
    std::vector<char> serializar() override {
        return this->estadoJuego.serializar();
    }

    void deserializar(std::vector<char> &serializado) override {
        this->estadoJuego.deserializar(serializado);
    }

private:
    EstadoJuego &estadoJuego;
};

#endif
