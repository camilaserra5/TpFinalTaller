#include "../include/modelo.h"


Modelo::Modelo(Ventana* ventana, int idJugador):
    ventana(ventana),
    idJugador(idJugador),
    jugadores(),
    entidades(){}

Modelo::~Modelo(){}

void Modelo::inicializar(){
      Player* player = new Player("../../client/resources/images/Weapons.png", this->ventana->obtener_render(), this->idJugador);
      this->jugadores.insert(std::make_pair(this->idJugador, player));
}

void Modelo::actualizarJugador(int x, int y, int vida, int angulo, int id, int idArma){
    this->jugadores[id]->settear_estado(x,y,vida,angulo, idArma);
}

void Modelo::renderizar(){
      this->jugadores[this->idJugador]->renderizar();
}


