#include "../include/estadoJuego.h"
#define METROS_MOVIDOS 1 // de acuanto se mueve el jugador


EstadoJuego::EstadoJuego(Map& mapa, std::map<int, Jugador>& jugadores):
    mapa(mapa),
    jugadores(jugadores){}

EstadoJuego::~EstadoJuego(){}

bool puedo_moverme(Map& mapa, int& posx, int& posy){
  Type tipo = mapa(posx, posy);
  if (tipo == Type::wall){
        return false;
  } else if (tipo == Type::door) {
      // verifico si tengo llave sino no puedo avanzar;
      return false;
  } else if (tipo == Type::keyDoor) {
      // me guardo la llave
      return true;
  } else if (tipo == Type::fakeDoor){
      return false;
  } else {
      return true;
  }
}
void EstadoJuego::moverse_a_derecha(int idJugador){
    Jugador jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int posEnJuegox = jugador.posEnX() + METROS_MOVIDOS;
    int posEnJuegoy = jugador.posEnY();
    if (puedo_moverme(this->mapa, posEnJuegox, posEnJuegoy)){
        jugador.moverse(METROS_MOVIDOS, 0); // en jugador se recibe lo movido y se suma;
    } else {
        this->no_me_muevo(idJugador);
    }

}

void EstadoJuego::moverse_a_izquierda(int idJugador){
    Jugador jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int posEnJuegox = jugador.posEnX() - METROS_MOVIDOS;
    int posEnJuegoy = jugador.posEnY();
    if (puedo_moverme(this->mapa, posEnJuegox, posEnJuegoy)){
        jugador.moverse(-METROS_MOVIDOS, 0); // en jugador se recibe lo movido y se suma;
    } else {
        this->no_me_muevo(idJugador);
    }
}

void EstadoJuego::moverse_arriba(int idJugador){
    Jugador jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int posEnJuegox = jugador.posEnX();
    int posEnJuegoy = jugador.posEnY() + METROS_MOVIDOS;
    if (puedo_moverme(this->mapa, posEnJuegox, posEnJuegoy)){
        jugador.moverse(0, METROS_MOVIDOS); // en jugador se recibe lo movido y se suma;
    } else {
        this->no_me_muevo(idJugador);
    }
}
void EstadoJuego::moverse_abajo(int idJugador){
    Jugador jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int posEnJuegox = jugador.posEnX();
    int posEnJuegoy = jugador.posEnY() - METROS_MOVIDOS;
    if (puedo_moverme(this->mapa, posEnJuegox, posEnJuegoy)){
        jugador.moverse(0, -METROS_MOVIDOS); // en jugador se recibe lo movido y se suma;
    } else {
        this->no_me_muevo(idJugador);
    }
}
void EstadoJuego::no_me_muevo(int idJugador){
    Jugador jugador = this->jugadores.at(idJugador);
    jugador.moverse(0,0);
}
