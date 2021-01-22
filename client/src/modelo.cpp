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

void Modelo::renderizar(){
      this->jugadores[this->idJugador]->settear_estado(200,200, 100, 50);
    this->jugadores[this->idJugador]->renderizar();
}

void Modelo::actualizarJugador(int x, int y, int vida, int angulo, int id){
      this->jugadores[id]->settear_estado(x,y,vida,angulo/*tipo de arma*/);
}
