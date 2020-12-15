#include "../include/estadoJuego.h"
#include "items/item.h"
#include "items/comida.h"
#include "items/balas.h"
#include "items/sangre.h"
#include "items/kitsMedicos.h"
#include "items/noItem.h"
#include "iostream"

#define METROS_MOVIDOS 1 // de acuanto se mueve el jugador

void EstadoJuego::realizarAtaque(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador);
    Arma *arma = jugador->getArma();
    int distancia_inventada = 5;
    arma->atacar(distancia_inventada, jugador, this->jugadores);
}

EstadoJuego::EstadoJuego(Map &mapa) :
        mapa(mapa),
        jugadores() {}

EstadoJuego::~EstadoJuego() {
    std::map<int, Jugador *>::iterator it;
    for (it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
        delete it->second;
    }
}

void EstadoJuego::agregarJugador(std::string &nombreJugador, int &id) {
    Jugador *jugador = new Jugador(nombreJugador, id);
    this->jugadores.insert(std::make_pair(id, jugador));
}

bool puedo_moverme(Map &mapa, int &posx, int &posy) {

    Type tipo = mapa(posx, posy);
    if (tipo == Type::wall) {
        return false;
    } else if (tipo == Type::door) {
        // verifico si tengo llave sino no puedo avanzar;
        return false;
    } else if (tipo == Type::keyDoor) {
        // me guardo la llave
        return true;
    } else if (tipo == Type::fakeDoor) {
        return false;
    } else {
        std::cout << "puedo moverme";
        return true;
    }
}

Item *verificarItems(Map &mapa, int &posx, int &posy) {
    Type tipo = mapa(posx, posy);
    if (tipo == Type::comida) {
        return new Comida();
    } else if (tipo == Type::sangre) {
        return new Sangre();
    } else if (tipo == Type::kitsMedicos) {

        return new KitsMedicos();
    } else if (tipo == Type::balas) {
        return new Balas();
        // faltan mas comandos, las armas!!
    } else {
        return new NoItem();
    }
}

void EstadoJuego::moverse_a_derecha(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int posEnJuegox = jugador->posEnX() + METROS_MOVIDOS;
    int posEnJuegoy = jugador->posEnY();
    std::cout << "pos juador x antes de actualizar: " << jugador->posEnX();
    std::cout << "pos jugador en y ants de actualzia: " << jugador->posEnY();
    std::cout << "pos en x: " << posEnJuegox;
    std::cout << "pos en y: " << posEnJuegoy;
    if (puedo_moverme(this->mapa, posEnJuegox, posEnJuegoy)) {
        Item *item = verificarItems(this->mapa, posEnJuegox, posEnJuegoy);
        item->obtenerBeneficio(jugador);
        jugador->moverse(METROS_MOVIDOS, 0); // en jugador se recibe lo movido y se suma;
        delete item;
    } else {
        this->no_me_muevo(idJugador);
    }

}

void EstadoJuego::moverse_a_izquierda(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int posEnJuegox = jugador->posEnX() - METROS_MOVIDOS;
    int posEnJuegoy = jugador->posEnY();
    if (puedo_moverme(this->mapa, posEnJuegox, posEnJuegoy)) {
        Item *item = verificarItems(this->mapa, posEnJuegox, posEnJuegoy);
        item->obtenerBeneficio(jugador);
        jugador->moverse(-METROS_MOVIDOS, 0); // en jugador se recibe lo movido y se suma;
    } else {
        this->no_me_muevo(idJugador);
    }
}

void EstadoJuego::moverse_arriba(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int posEnJuegox = jugador->posEnX();
    int posEnJuegoy = jugador->posEnY() + METROS_MOVIDOS;
    if (puedo_moverme(this->mapa, posEnJuegox, posEnJuegoy)) {
        Item *item = verificarItems(this->mapa, posEnJuegox, posEnJuegoy);
        item->obtenerBeneficio(jugador);
        jugador->moverse(0, METROS_MOVIDOS); // en jugador se recibe lo movido y se suma;
    } else {
        this->no_me_muevo(idJugador);
    }
}

void EstadoJuego::moverse_abajo(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int posEnJuegox = jugador->posEnX();
    int posEnJuegoy = jugador->posEnY() - METROS_MOVIDOS;
    if (puedo_moverme(this->mapa, posEnJuegox, posEnJuegoy)) {
        Item *item = verificarItems(this->mapa, posEnJuegox, posEnJuegoy);
        item->obtenerBeneficio(jugador);
        jugador->moverse(0, -METROS_MOVIDOS); // en jugador se recibe lo movido y se suma;
    } else {
        this->no_me_muevo(idJugador);
    }
}

void EstadoJuego::no_me_muevo(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador);
    jugador->moverse(0, 0);
}
