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
#include "iostream"

#define METROS_MOVIDOS 1 // de acuanto se mueve el jugador

void EstadoJuego::realizarAtaque(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador);
    Arma *arma = jugador->getArma();
    int distancia_inventada = 5;
    arma->atacar(distancia_inventada, jugador, this->jugadores);
}

EstadoJuego::EstadoJuego(Map *mapa) :
        mapa(mapa),
        jugadores() {}

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
        // verifico si tengo llave sino no puedo avanzar;
        if (jugador->tengollave()) {
            // abrir puerta;
            jugador->usarLlave();
            return true;
        }
        return false;
    } else if (tipo == Type::keyDoor) {
        // me guardo la llave
        Posicion posicion(1, 1, 1);//va a depender de su posidion en el mapa
        Llave llave(posicion);
        llave.obtenerBeneficio(mapa->obtenerContenedor(), jugador);
        return true;
    } else if (tipo == Type::fakeDoor) {
        return false;
    } else {
        std::cout << "puedo moverme\n";
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

/*
    Posicion posicion = Posicion(1,1,0.5);//va a depender de su posidion en el mapa
    Type tipo = mapa->operator()(posEnMapaJugadorx, posEnMapaJugadory);
    if (tipo == Type::comida) {
        return new Comida(posicion);
    } else if (tipo == Type::sangre) {
        return new Sangre(posicion);
    } else if (tipo == Type::kitsMedicos) {
        return new KitsMedicos(posicion);
    } else if (tipo == Type::balas) {
        return new Balas(posicion);
    } else if (tipo == Type::ametralladora) {
        return new Ametralladora(posicion);
    } else if (tipo == Type::canionDeCadena){
        return new CanionDeCadena(posicion);
    } else if (tipo == Type::lanzaCohetes){
        //return new lanzaCohetes();
    } else if (tipo == Type::tesoro){
        std::string tesoro("copa");
        int puntos = 50;
        return new Tesoro(tesoro, puntos,posicion);
    } else {
        return new NoItem(posicion);
    }*/
}

void EstadoJuego::buscarItemsEnPosJugador(Jugador* jugador,int& posX,int& posY, int xFinal, int yFinal){
  if (puedo_moverme(this->mapa, posX, posY, jugador)) {
      Item *item = verificarItems(this->mapa, posX, posY);
      item->obtenerBeneficio(this->mapa->obtenerContenedor(), jugador);
      jugador->moverse(xFinal, yFinal); // en jugador se recibe lo movido y se suma;
      delete item;
  } else {
      jugador->moverse(0,0);
  }
}

void EstadoJuego::moverse_a_derecha(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int posEnJuegox = jugador->posEnX() + METROS_MOVIDOS;
    int posEnJuegoy = jugador->posEnY();
    std::cout << "pos x: " << posEnJuegox << "\n";
    std::cout << "pos y: " << posEnJuegoy << "\n";
    this->buscarItemsEnPosJugador(jugador,posEnJuegox,posEnJuegoy,METROS_MOVIDOS,0);

    /*
    if (puedo_moverme(this->mapa, posEnJuegox, posEnJuegoy, jugador)) {
        Item *item = verificarItems(this->mapa, posEnJuegox, posEnJuegoy);
        item->obtenerBeneficio(this->mapa->obtenerContenedor(), jugador);
        jugador->moverse(METROS_MOVIDOS, 0); // en jugador se recibe lo movido y se suma;
    } else {
        this->no_me_muevo(idJugador);
    }
*/
}

void EstadoJuego::moverse_a_izquierda(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int posEnJuegox = jugador->posEnX() - METROS_MOVIDOS;
    int posEnJuegoy = jugador->posEnY();
    this->buscarItemsEnPosJugador(jugador,posEnJuegox,posEnJuegoy,-METROS_MOVIDOS,0);
    /*
    if (puedo_moverme(this->mapa, posEnJuegox, posEnJuegoy, jugador)) {
        Item *item = verificarItems(this->mapa, posEnJuegox, posEnJuegoy);
        item->obtenerBeneficio(this->mapa->obtenerContenedor(), jugador);
        jugador->moverse(-METROS_MOVIDOS, 0); // en jugador se recibe lo movido y se suma;
    } else {
        this->no_me_muevo(idJugador);
    }*/
}

void EstadoJuego::moverse_arriba(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int posEnJuegox = jugador->posEnX();
    int posEnJuegoy = jugador->posEnY() + METROS_MOVIDOS;
    this->buscarItemsEnPosJugador(jugador,posEnJuegox,posEnJuegoy,0,METROS_MOVIDOS);
/*
    if (puedo_moverme(this->mapa, posEnJuegox, posEnJuegoy, jugador)) {
        Item *item = verificarItems(this->mapa, posEnJuegox, posEnJuegoy);
        item->obtenerBeneficio(this->mapa->obtenerContenedor(), jugador);
        jugador->moverse(0, METROS_MOVIDOS); // en jugador se recibe lo movido y se suma;
    } else {
        this->no_me_muevo(idJugador);
    }
    */
}

void EstadoJuego::moverse_abajo(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int posEnJuegox = jugador->posEnX();
    int posEnJuegoy = jugador->posEnY() - METROS_MOVIDOS;
    this->buscarItemsEnPosJugador(jugador,posEnJuegox,posEnJuegoy,0,-METROS_MOVIDOS);
/*
    if (puedo_moverme(this->mapa, posEnJuegox, posEnJuegoy, jugador)) {
        Item *item = verificarItems(this->mapa, posEnJuegox, posEnJuegoy);
        item->obtenerBeneficio(this->mapa->obtenerContenedor(), jugador);
        jugador->moverse(0, -METROS_MOVIDOS); // en jugador se recibe lo movido y se suma;
    } else {
        this->no_me_muevo(idJugador);
    }
    */
}

void EstadoJuego::no_me_muevo(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador);
    jugador->moverse(0, 0);
}

void EstadoJuego::verificarJugadoresMuertos() {
    std::map<int, Jugador *>::iterator it;
    for (it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
        if (it->second->estaMuerto()) {
            Arma *arma = it->second->getArma();
            if (!arma->esPistola()) {
                //Item* item = arma;
                //  this->mapa->agregarElemento(item);//como lo pasamos a item
            }
            this->mapa->agregarElemento(new Balas(it->second->getPosicion(), 10/*cte*/));
            if (it->second->tengollave()) {
                this->mapa->agregarElemento(
                        new Llave(it->second->getPosicion()));//hay que cambiarlo a que el jugador se guarde una llave
            }
        }
    }
}
