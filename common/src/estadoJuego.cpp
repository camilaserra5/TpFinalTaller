#include "../include/estadoJuego.h"
#include "items/item.h"
#include "items/comida.h"
#include "items/balas.h"
#include "items/sangre.h"
#include "items/kitsMedicos.h"
#include "items/noItem.h"
#include "items/llave.h"
#include "items/tesoro.h"
#include "armas/canionDeCadena.h"
#include "armas/ametralladora.h"
#include "armas/pistola.h"
#include "armas/cuchillo.h"
#include "iostream"
#include "puerta.h"
#include <math.h>

#define ROTACION_DERECHA -1
#define ROTACION_IZQUIERDA 1
#define METROS_MOVIDOS 2 // de acuanto se mueve el jugador
#define CANT_TICKS_PARTIDA 10000  //5min

void EstadoJuego::abrirPuerta(int idJugador){
  Jugador* jugador = this->jugadores.at(idJugador);
  Posicion& posJugador = jugador->getPosicion();
  double distancia;
  if (this->mapa->hayPuertas()){
    Puerta& puertaMasCercana = this->mapa->puertaMasCercana(posJugador,distancia);//obtengo la puerta mas proxima al jugador
    if (puertaMasCercana.puedeSerAbierta(jugador->tengollave(),distancia)){
      puertaMasCercana.abrir();
    }
  }
}

void EstadoJuego::realizarAtaque(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador);
    Arma *arma = jugador->getArma();
    int distancia_inventada = 5;
    arma->atacar(distancia_inventada, jugador, this->jugadores);
}

EstadoJuego::EstadoJuego(Map *mapa) :
        mapa(mapa),
        jugadores(),
        contador(0){}

EstadoJuego::~EstadoJuego() {
    std::cout << "destructor estado juego";
    delete this->mapa;
    std::map<int, Jugador *>::iterator it;
    for (it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
        delete it->second;
    }
}

void EstadoJuego::agregarJugador(std::string &nombreJugador, int &id) {
    Jugador *jugador = new Jugador(nombreJugador, id);
    this->jugadores.insert(std::make_pair(id, jugador));
}

bool puedo_moverme(Map *mapa, int &posx, int &posy, Jugador *jugador) {
    int posEnMapaJugadorx =
            (mapa->getRowSize() * posx) / (mapa->getRowSize() * 50);  // 50 seria el tamanio de la celda en pixeles
    // esa info hya que ver quien la tiene. maybe mapa?
    int posEnMapaJugadory = (mapa->getColSize() * posy) / (mapa->getColSize() * 50);

    Type tipo = mapa->operator()(posEnMapaJugadorx, posEnMapaJugadorx);
    if (tipo == Type::wall) {
        return false;
    } else if (tipo == Type::door) {
        return false;
    } else if (tipo == Type::fakeDoor) {
        return false;
    } else {
        return true;
    }
}

Item *verificarItems(Map *mapa, int &posx, int &posy) {
    int posEnMapaJugadorx =
            (mapa->getRowSize() * posx) / (mapa->getRowSize() * 50);  // 50 seria el tamanio de la celda en pixeles
    // esa info hya que ver quien la tiene. maybe mapa?
    int posEnMapaJugadory = (mapa->getColSize() * posy) / (mapa->getColSize() * 50);
    std::cout << "\n verifico item\n";
    return mapa->buscarElemento(posx, posy);
}

void EstadoJuego::verificarMovimientoJugador(Jugador* jugador,int& xFinal,int& yFinal){
  bool obtuvoBeneficio = false;
  if (puedo_moverme(this->mapa, xFinal, yFinal, jugador)) {
      Item *item = verificarItems(this->mapa, xFinal, yFinal);
      obtuvoBeneficio = item->obtenerBeneficio(jugador);
      if (obtuvoBeneficio){
        this->mapa->sacarDelMapa(item->getPosicion());
      }
      jugador->moverse(xFinal, yFinal); // en jugador se recibe lo movido y se suma;
      delete item;// a cheqeuar
  }
}

void EstadoJuego::rotar_a_derecha(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    jugador->rotar(ROTACION_DERECHA);

    //this->verificarMovimientoJugador(jugador,posEnJuegox,posEnJuegoy,METROS_MOVIDOS,0);

}

void EstadoJuego::rotar_a_izquierda(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    jugador->rotar(ROTACION_IZQUIERDA);
  //  int posEnJuegox = jugador->posEnX() - METROS_MOVIDOS;
  //  int posEnJuegoy = jugador->posEnY();
    //this->buscarItemsEnPosJugador(jugador,posEnJuegox,posEnJuegoy,-METROS_MOVIDOS,0);

}

void EstadoJuego::moverse_arriba(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int xFinal = jugador->posEnX() + (METROS_MOVIDOS * cos(jugador->getAnguloDeVista()));
    int yFinal = jugador->posEnY() + (METROS_MOVIDOS* sin(jugador->getAnguloDeVista()));
    this->verificarMovimientoJugador(jugador,xFinal,yFinal);
}

void EstadoJuego::moverse_abajo(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int xFinal = jugador->posEnX() - (METROS_MOVIDOS * cos(jugador->getAnguloDeVista()));
    int yFinal = jugador->posEnY() - (METROS_MOVIDOS * sin(jugador->getAnguloDeVista()));
    this->verificarMovimientoJugador(jugador,xFinal,yFinal);
}

void EstadoJuego::no_me_muevo(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador);
    jugador->moverse(0, 0);
}

void EstadoJuego::verificarJugadoresMuertos() {
    std::map<int, Jugador *>::iterator it;
    for (it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
        if (it->second->estaMuerto()) {
            if (it->second->cant_de_vida()>0){
                it->second->actualizarNuevaVida();
            } else {
                this->jugadoresMuertos++;
            }
            Arma *arma = it->second->getArma();

            if (arma->getTipo() == Type::pistola && arma->getTipo() == Type::cuchillo){
                this->mapa->agregarArma(it->second->getPosicion(),arma);
            }
            this->mapa->agregarElemento(new Balas(it->second->getPosicion(), 10/*cte*/, static_cast<int>(Type::balas)));
            if (it->second->tengollave()) {
                this->mapa->agregarElemento(
                        new Llave(it->second->getPosicion(), static_cast<int>(Type::keyDoor)));//hay que cambiarlo a que el jugador se guarde una llave
            }
        }
    }
}
bool EstadoJuego::terminoPartida(){
      bool termino = false;
      if ((this->jugadoresMuertos == this->jugadores.size() -1) ||
            this->contador == 0){
                termino = true;
        }
        return termino;

}

void EstadoJuego::lanzarContadorTiempoPartida(){
    this->contador = CANT_TICKS_PARTIDA;
}

void EstadoJuego::actualizarTiempoPartida(){
    this->contador--;
}
