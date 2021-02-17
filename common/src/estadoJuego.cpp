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
#include "../include/actualizaciones/actualizacionMovimiento.h"
#include "../include/actualizaciones/actualizacionAperturaPuerta.h"
#include "../include/actualizaciones/actualizacionAgarroItem.h"


#define ROTACION_DERECHA -1
#define ROTACION_IZQUIERDA 1
#define METROS_MOVIDOS 20
#define CANT_TICKS_PARTIDA 10000  //5min

Actualizacion *EstadoJuego::abrirPuerta(int idJugador) {
    Actualizacion *actualizacion = NULL;
    Jugador *jugador = this->jugadores.at(idJugador);
    jugador->dejarDeDisparar();
    Posicion &posJugador = jugador->getPosicion();
    double distancia;
    if (this->mapa.hayPuertas()) {
        Puerta &puertaMasCercana = this->mapa.puertaMasCercana(posJugador,
                                                               distancia);
        if (puertaMasCercana.puedeSerAbierta(jugador->tengollave(), distancia)) {
            puertaMasCercana.abrir();
            actualizacion = new ActualizacionAperturaPuerta(puertaMasCercana);
        }
    }
    return actualizacion;
}

EstadoJuego::EstadoJuego() {}

Actualizacion *EstadoJuego::realizarAtaque(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador);
    std::cerr << "jugador id: " << jugador->getId() << "\n";
    jugador->atacar();
    Arma *arma = jugador->getArma();
    std::cerr << "arma : " << arma->getTipo().getName() << "\n";
    int distancia_inventada = 5;
    Actualizacion *actualizacion = arma->atacar(distancia_inventada, jugador, this->jugadores);
    return actualizacion;
}

EstadoJuego::EstadoJuego(Map &mapa) :
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
    std::cerr << "agrego un jugadorrr"<< std::endl;
    if(!jugador){
        std::cerr << "O NO..."<< std::endl;
    }
    this->jugadores.insert(std::make_pair(id, jugador));
}

bool puedo_moverme(Map &mapa, int &posx, int &posy, Jugador *jugador) {
    if (posx < 0 || posy < 0 || posx > (mapa.getRowSize() * mapa.getLadoCelda() - 1) || posy > (mapa.getColSize() * mapa.getLadoCelda() - 1)) return false;
    int posEnMapaJugadorx = posx / mapa.getLadoCelda();  // 50 seria el tamanio de la celda en pixeles
    // esa info hya que ver quien la tiene. maybe mapa?
    int posEnMapaJugadory = posy / mapa.getLadoCelda();
  //  std::cerr << "pos del jugador q verifico x: " << posEnMapaJugadorx << " y: " << posEnMapaJugadory << std::endl;
    Type tipo = mapa.operator()(posEnMapaJugadorx, posEnMapaJugadorx);
    std::string name = tipo.getName();
//dstd::cerr << "name: " << name << "\n";
    return (name != "door" && name != "wall" && name != "wall-2" && name != "wall-3" && name != "fakeDoor" &&
            name != "keyDoor");
}

Item *verificarItems(Map &mapa, int &posx, int &posy) {
    int posEnMapaJugadorx =
            (mapa.getRowSize() * posx) / (mapa.getRowSize() * mapa.getLadoCelda());
    // esa info hya que ver quien la tiene. maybe mapa?
    int posEnMapaJugadory = (mapa.getColSize() * posy) / (mapa.getColSize() * mapa.getLadoCelda());
  //s  std::cout << "\n verifico item\n";
    return mapa.buscarElemento(posx, posy);
}

std::vector<Actualizacion *> EstadoJuego::verificarMovimientoJugador(Jugador *jugador, int &xFinal, int &yFinal) {
    bool obtuvoBeneficio = false;
    std::vector<Actualizacion *> actualizaciones;
    if (puedo_moverme(this->mapa, xFinal, yFinal, jugador)) {
        //std::cerr << "/* PUDE MOVER A JUGADOOR A */" << xFinal << " " << yFinal << '\n';
        Item *item = verificarItems(this->mapa, xFinal, yFinal);
        if (item != nullptr) {
            obtuvoBeneficio = item->obtenerBeneficio(jugador);
            Actualizacion *obtengoItem = new ActualizacionAgarroItem(jugador, item);
            actualizaciones.push_back(obtengoItem);
            if (obtuvoBeneficio) {
                this->mapa.sacarDelMapa(item->getPosicion());
            }
        }
        jugador->moverse(xFinal, yFinal);
    }
    actualizaciones.push_back(new ActualizacionMovimiento(jugador));
    return actualizaciones;
}

Actualizacion *EstadoJuego::rotar_a_derecha(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    //jugador->dejarDeDisparar();
    jugador->rotar(ROTACION_DERECHA);
    return new ActualizacionMovimiento(jugador);
}

Actualizacion *EstadoJuego::rotar_a_izquierda(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    //jugador->dejarDeDisparar();
    jugador->rotar(ROTACION_IZQUIERDA);
    return new ActualizacionMovimiento(jugador);
}

std::vector<Actualizacion *> EstadoJuego::moverse_arriba(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    //  jugador->dejarDeDisparar();
  //  std::cerr << "ME MUEVO ARRIBAAAA\n";
  //  std::cerr << "angulo juagdor: " << jugador->getAnguloDeVista();
//    std::cerr << "pos ant x" << jugador->posEnX() << " y" << jugador->posEnY() << std::endl;
    int xFinal = jugador->posEnX() + (METROS_MOVIDOS * cos(jugador->getAnguloDeVista()));
    int yFinal = jugador->posEnY() + (METROS_MOVIDOS * (-1) * sin(jugador->getAnguloDeVista()));
  //  std::cerr << "pos dsp x" << xFinal << " y" << yFinal << std::endl;
    return this->verificarMovimientoJugador(jugador, xFinal, yFinal);
}

std::vector<Actualizacion *> EstadoJuego::moverse_abajo(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    //jugador->dejarDeDisparar();

    //std::cerr << "angulo juagdor: " << jugador->getAnguloDeVista();
  //  std::cerr << "pos ant x" << jugador->posEnX() << " y" << jugador->posEnY() << std::endl;
    int xFinal = jugador->posEnX() + (METROS_MOVIDOS * (-1 ) * cos(jugador->getAnguloDeVista()));
    int yFinal = jugador->posEnY() + (METROS_MOVIDOS * sin(jugador->getAnguloDeVista()));
  //  std::cerr << "pos dsp x" << xFinal << " y" << yFinal << std::endl;
    return this->verificarMovimientoJugador(jugador, xFinal, yFinal);
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
    //  std::cerr << "estado juego deserializar empieza" << std::endl;
    int idx = 0;
    sub = std::vector<char>(&informacion[idx], &informacion[idx + 4]);
    int jugadoresSize = charArrayToNumber(sub);
    //std::cerr << "estado juego deserializar jugadores size" << jugadoresSize << std::endl;
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
    std::cerr << "tam vector: " << informacion.size() << " y el idx es: " << idx << std::endl;
    std::vector<char> mapaSerializado(informacion.begin() + idx,
                                      informacion.end());
      this->mapa.deserializar(mapaSerializado);


    //std::cerr << "estado juego deserializar fin" << std::endl;
}

std::map<int, Jugador *> &EstadoJuego::obtenerJugadores() {
    return this->jugadores;
}

Map &EstadoJuego::obtenerMapa() {
    return this->mapa;
}

Actualizacion *EstadoJuego::cambiarArma(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador);
    return jugador->cambiarArma();
}
std::vector<std::vector<int>> EstadoJuego::GetMapanumerico(){
    return this->mapa.getMapanumerico();
}

std::vector<int> EstadoJuego::getPosicionJugador(int idJugador){
    Jugador *jugador = this->jugadores.at(idJugador); //No se por que falla :( carita triste
    int posEnMapaJugadorx = jugador->posEnX() / mapa.getLadoCelda();
    int posEnMapaJugadory = jugador->posEnY() / mapa.getLadoCelda();
    std::vector<int> posiciones;
    posiciones.push_back(posEnMapaJugadorx);
    posiciones.push_back(posEnMapaJugadory);
    return posiciones;
}
