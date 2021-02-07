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
#define METROS_MOVIDOS 2
#define CANT_TICKS_PARTIDA 10000  //5min
#define TAMANIO_CELDA 40 //es variable y depende del tamanio del mapa

void EstadoJuego::abrirPuerta(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador);
    Posicion &posJugador = jugador->getPosicion();
    double distancia;
    if (this->mapa.hayPuertas()) {
        Puerta &puertaMasCercana = this->mapa.puertaMasCercana(posJugador,
                                                                distancia);
        if (puertaMasCercana.puedeSerAbierta(jugador->tengollave(), distancia)) {
            puertaMasCercana.abrir();
        }
    }
}

EstadoJuego::EstadoJuego() {}

void EstadoJuego::realizarAtaque(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador);
    jugador->atacar();
    Arma *arma = jugador->getArma();
    int distancia_inventada = 5;
    arma->atacar(distancia_inventada, jugador, this->jugadores);
}

EstadoJuego::EstadoJuego(Map& mapa) :
        mapa(mapa),
        jugadores(),
        contador(0) {}

EstadoJuego::~EstadoJuego() {
    std::map<int, Jugador *>::iterator it;
    for (it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
        delete it->second;
    }
}

void EstadoJuego::agregarJugador(std::string &nombreJugador, int &id) {
    Posicion posicionValida = this->mapa.obtenerPosicionIncialValida();
    Jugador *jugador = new Jugador(nombreJugador, id, posicionValida);
    this->jugadores.insert(std::make_pair(id, jugador));
}

bool puedo_moverme(Map& mapa, int &posx, int &posy, Jugador *jugador) {
    int posEnMapaJugadorx =
            (mapa.getRowSize() * posx) /
            (mapa.getRowSize() * TAMANIO_CELDA);  // 50 seria el tamanio de la celda en pixeles
    // esa info hya que ver quien la tiene. maybe mapa?
    int posEnMapaJugadory = (mapa.getColSize() * posy) / (mapa.getColSize() * TAMANIO_CELDA);

    Type tipo = mapa.operator()(posEnMapaJugadorx, posEnMapaJugadorx);
    if (tipo.getName() == "wall") {
        return false;
    } else if (tipo.getName() == "door") {
        return false;
    } else if (tipo.getName() == "fakeDoor") {
        return false;
    } else {
        return true;
    }
}

Item *verificarItems(Map& mapa, int &posx, int &posy) {
    int posEnMapaJugadorx =
            (mapa.getRowSize() * posx) / (mapa.getRowSize() * TAMANIO_CELDA);
    // esa info hya que ver quien la tiene. maybe mapa?
    int posEnMapaJugadory = (mapa.getColSize() * posy) / (mapa.getColSize() * TAMANIO_CELDA);
    std::cout << "\n verifico item\n";
    return mapa.buscarElemento(posx, posy);
}

void EstadoJuego::verificarMovimientoJugador(Jugador *jugador, int &xFinal, int &yFinal) {
    bool obtuvoBeneficio = false;
    if (puedo_moverme(this->mapa, xFinal, yFinal, jugador)) {
        Item *item = verificarItems(this->mapa, xFinal, yFinal);
        obtuvoBeneficio = item->obtenerBeneficio(jugador);
        if (obtuvoBeneficio) {
            this->mapa.sacarDelMapa(item->getPosicion());
        }
        jugador->moverse(xFinal, yFinal);
        delete item;// a cheqeuar
    }
}

void EstadoJuego::rotar_a_derecha(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    jugador->rotar(ROTACION_DERECHA);
}

void EstadoJuego::rotar_a_izquierda(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    jugador->rotar(ROTACION_IZQUIERDA);

}

void EstadoJuego::moverse_arriba(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int xFinal = jugador->posEnX() + (METROS_MOVIDOS * cos(jugador->getAnguloDeVista()));
    int yFinal = jugador->posEnY() + (METROS_MOVIDOS * sin(jugador->getAnguloDeVista()));
    this->verificarMovimientoJugador(jugador, xFinal, yFinal);
}

void EstadoJuego::moverse_abajo(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int xFinal = jugador->posEnX() - (METROS_MOVIDOS * cos(jugador->getAnguloDeVista()));
    int yFinal = jugador->posEnY() - (METROS_MOVIDOS * sin(jugador->getAnguloDeVista()));
    this->verificarMovimientoJugador(jugador, xFinal, yFinal);
}

void EstadoJuego::no_me_muevo(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador);
    jugador->moverse(0, 0);
}

void EstadoJuego::verificarJugadoresMuertos() {
    std::map<int, Jugador *>::iterator it;
    for (it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
        if (it->second->estaMuerto()) {
            if (it->second->cant_de_vida() > 0) {
                it->second->actualizarNuevaVida();
            } else {
                this->jugadoresMuertos++;
            }
            Arma *arma = it->second->getArma();

            if (arma->getTipo().getName() == "pistola" && arma->getTipo().getName() == "cuchillo") {
                this->mapa.agregarArma(it->second->getPosicion(), arma);
            }
            this->mapa.agregarElemento(
                    new Balas(it->second->getPosicion(), 10/*cte*/,
                              ObjetosJuego::obtenerTipoPorNombre("balas").getType()));
            if (it->second->tengollave()) {
                this->mapa.agregarElemento(
                        new Llave(it->second->getPosicion(),
                                  ObjetosJuego::obtenerTipoPorNombre(
                                          "keyDoor").getType()));//hay que cambiarlo a que el jugador se guarde una llave
            }
        }
    }
}

bool EstadoJuego::terminoPartida() {
    bool termino = false;
    std::cout << "JUGADORES MUERTOS: " << this->jugadoresMuertos << "\n";
    std::cout << "CANTIDAD JUGADORES: " << this->jugadores.size() << "\n";

    if ((this->jugadoresMuertos == this->jugadores.size() - 1) ||
        this->contador == 0) {
        termino = true;
    }
    return termino;

}

void EstadoJuego::lanzarContadorTiempoPartida() {
    this->contador = CANT_TICKS_PARTIDA;
}

void EstadoJuego::actualizarTiempoPartida() {
    this->contador--;
}

std::vector<char> EstadoJuego::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(jugadores.size());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    std::map<int, Jugador *>::iterator it;
    for (it = jugadores.begin(); it != jugadores.end(); ++it) {
        Jugador jugador = *it->second;
        std::vector<char> jugadorSerializado = jugador.serializar();
        aux = numberToCharArray(jugadorSerializado.size());
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        informacion.insert(informacion.end(), jugadorSerializado.begin(), jugadorSerializado.end());
    }
    std::vector<char> mapaSerializado = mapa.serializar();
    informacion.insert(informacion.end(), mapaSerializado.begin(), mapaSerializado.end());
    return informacion;
}

void EstadoJuego::deserializar(std::vector<char> &informacion) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&informacion[idx], &informacion[idx + 4]);
    int jugadoresSize = charArrayToNumber(sub);
    idx += 4;
    for (int i = 0; i < jugadoresSize; i++) {
        sub = std::vector<char>(&informacion[idx], &informacion[idx + 4]);
        idx += 4;
        std::vector<char> jugadorSerializado(informacion.begin() + idx,
                                             informacion.begin() + idx + charArrayToNumber(sub));
        idx += charArrayToNumber(sub);
        Jugador *jugador = new Jugador();
        jugador->deserializar(jugadorSerializado);
        this->jugadores.insert(std::make_pair(jugador->getId(), jugador));
    }
    std::vector<char> mapaSerializado(informacion.begin() + idx,
                                      informacion.end());
    this->mapa.deserializar(mapaSerializado);
}

std::map<int, Jugador *> &EstadoJuego::obtenerJugadores() {
    return this->jugadores;
}

Map& EstadoJuego::obtenerMapa() {
    return this->mapa;
}

void EstadoJuego::cambiarArma(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador);
    jugador->cambiarArma();
}
