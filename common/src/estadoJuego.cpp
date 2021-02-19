#include "../include/estadoJuego.h"
#include "armas/lanzacohetes.h"
#include <math.h>
#include "../include/actualizaciones/actualizacionMovimiento.h"
#include "../include/actualizaciones/actualizacionAperturaPuerta.h"
#include "../include/actualizaciones/actualizacionAgarroItem.h"
#include "../include/actualizaciones/actualizacionAgregarItem.h"

#define ROTACION_DERECHA -1
#define ROTACION_IZQUIERDA 1
#define METROS_MOVIDOS 10
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

std::vector<Actualizacion *> EstadoJuego::realizarAtaque(int idJugador) {
    std::vector<Actualizacion *> actualizaciones;
    Jugador *jugador = this->jugadores.at(idJugador);
    std::cerr << "jugador id: " << jugador->getId() << "\n";
    jugador->atacar();
    Arma *arma = jugador->getArma();
    std::cerr << "arma : " << arma->getTipo().getName() << "\n";
    int distancia_inventada = 5;
    Actualizacion *actualizacionItem = this->verificarJugadoresMuertos();
    if (actualizacionItem != NULL) {
        actualizaciones.push_back(actualizacionItem);
    }
    Actualizacion *actualizacionAtaque = arma->atacar(distancia_inventada, jugador, this->jugadores);
    actualizaciones.push_back(actualizacionAtaque);
    return actualizaciones;
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
    std::cerr << "===========EL ID ES: " << id << std::endl;
    Posicion posicionValida = this->mapa.obtenerPosicionIncialValida();
    std::cerr << "la pos inicial valida es: " << posicionValida.pixelesEnX() << " y: " << posicionValida.pixelesEnY()
              << " angulo: " << posicionValida.getAnguloDeVista() << " id: " << id << "\n";
    Jugador *jugador = new Jugador(nombreJugador, id, posicionValida);
    std::cerr << "agrego un jugadorrr" << std::endl;
    if (!jugador) {
        std::cerr << "O NO..." << std::endl;
    }
    try {
        this->jugadores.insert(std::make_pair(id, jugador));
        std::cerr << "======CHEQUEO SI ESTA======" << std::endl;
        Jugador *jugadorchequeo = this->jugadores.at(id);
        std::cerr << "=============EL JUGADOR ES " << jugadorchequeo->obtenerNombre() << std::endl;
    } catch (...) {
        std::cerr << "======NO PUDE AGREGAR AL JUGADOR CON ID======" << std::endl;
    }

}

bool puedo_moverme(Map &mapa, int &posx, int &posy, Jugador *jugador) {
    int posXMax = mapa.getRowSize() * mapa.getLadoCelda() - 1;
    int posYMax = mapa.getColSize() * mapa.getLadoCelda() - 1;
    if (posx < 0 || posy < 0 || posx > posXMax || posy > posYMax) return false;
    int posEnMapaJugadorx = posx / mapa.getLadoCelda();
    int posEnMapaJugadory = posy / mapa.getLadoCelda();
    Type tipo = mapa.operator()(posEnMapaJugadorx, posEnMapaJugadory);
    std::string name = tipo.getName();
    return (name != "door" && name != "wall" && name != "wall-2" && name != "wall-3" && name != "fakeDoor" &&
            name != "keyDoor");
}

Item *EstadoJuego::verificarItems(int &posx, int &posy) {
    return mapa.buscarElemento(posx, posy);
}

std::vector<Actualizacion *> EstadoJuego::verificarMovimientoJugador(Jugador *jugador, int &xFinal, int &yFinal) {
    bool obtuvoBeneficio = false;
    std::vector<Actualizacion *> actualizaciones;
    if (puedo_moverme(this->mapa, xFinal, yFinal, jugador)) {
        Item *item = verificarItems(xFinal, yFinal);
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
    std::cerr << "jugador:  posx: " << jugador->posEnX() << "posy: " << jugador->posEnY() << "\n";
    actualizaciones.push_back(new ActualizacionMovimiento(jugador));
    return actualizaciones;
}

Actualizacion *EstadoJuego::rotar_a_derecha(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    jugador->rotar(ROTACION_DERECHA);
    return new ActualizacionMovimiento(jugador);
}

Actualizacion *EstadoJuego::rotar_a_izquierda(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    jugador->rotar(ROTACION_IZQUIERDA);
    return new ActualizacionMovimiento(jugador);
}

std::vector<Actualizacion *> EstadoJuego::moverse_arriba(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador

    int xFinal = jugador->posEnX() + (METROS_MOVIDOS * cos(jugador->getAnguloDeVista()));
    int yFinal = jugador->posEnY() + (METROS_MOVIDOS * (-1) * sin(jugador->getAnguloDeVista()));
    return this->verificarMovimientoJugador(jugador, xFinal, yFinal);
}

std::vector<Actualizacion *> EstadoJuego::moverse_abajo(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); // lanzar excepcion en caso de que no lo tenga al jugador
    int xFinal = jugador->posEnX() + (METROS_MOVIDOS * (-1) * cos(jugador->getAnguloDeVista()));
    int yFinal = jugador->posEnY() + (METROS_MOVIDOS * sin(jugador->getAnguloDeVista()));
    return this->verificarMovimientoJugador(jugador, xFinal, yFinal);
}

void EstadoJuego::no_me_muevo(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador);
    jugador->moverse(0, 0);

}

Actualizacion *EstadoJuego::verificarJugadoresMuertos() {
    std::map<int, Jugador *>::iterator it;
    Actualizacion *agregarItem = NULL;
    for (it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
        if (it->second->estaMuerto()) {
            std::cerr << "=========Se murio alguien :$========" << '\n';
            if (it->second->cant_de_vida() > 0) {
                it->second->actualizarNuevaVida();
            } else {
                this->jugadoresMuertos++;
                std::cerr << "========= Morision definitiva========" << '\n';
            }
            Arma *arma = it->second->getArma();
            Type tipo = arma->getTipo();
            if (tipo.getName() == "ametralladora") {
                Item *ametralladora = new Ametralladora(it->second->getPosicion(), mapa.crearIdValido());
                this->mapa.agregarElemento(ametralladora);
                agregarItem = new ActualizacionAgregarItem(ametralladora);
            } else if (tipo.getName() == "canionDeCadena") {
                Item *canion = new CanionDeCadena(it->second->getPosicion(), mapa.crearIdValido());
                this->mapa.agregarElemento(canion);
                agregarItem = new ActualizacionAgregarItem(canion);
            } else if (tipo.getName() == "lanzaCohetes") {
                Item *lanzaCohetes = new LanzaCohetes(it->second->getPosicion(), mapa.crearIdValido());
                this->mapa.agregarElemento(lanzaCohetes);
                agregarItem = new ActualizacionAgregarItem(lanzaCohetes);
            }
            Item *balas = new Balas(it->second->getPosicion(), 10/*cte*/, mapa.crearIdValido());
            this->mapa.agregarElemento(balas);
            agregarItem = new ActualizacionAgregarItem(balas);
            if (it->second->tengollave()) {
                Item *llave = new Llave(it->second->getPosicion(), mapa.crearIdValido());
                this->mapa.agregarElemento(llave);
                agregarItem = new ActualizacionAgregarItem(llave);
            }
        }
    }
    return agregarItem;
}

bool EstadoJuego::terminoPartida() {
    bool termino = false;
    int cantidadJugadores = this->jugadores.size();
    if ((this->jugadoresMuertos == cantidadJugadores - 1) || this->contador == 0) {
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
    std::cerr << "tam vector: " << informacion.size() << " y el idx es: " << idx << std::endl;
    std::vector<char> mapaSerializado(informacion.begin() + idx,
                                      informacion.end());
    this->mapa.deserializar(mapaSerializado);


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

std::vector<std::vector<int>> EstadoJuego::GetMapanumerico() {
    return this->mapa.getMapanumerico();
}

std::vector<int> EstadoJuego::getPosicionJugador(int idJugador) {
    Jugador *jugador = this->jugadores.at(idJugador); //No se por que falla :( carita triste
    int posEnMapaJugadorx = jugador->posEnX() / mapa.getLadoCelda();
    int posEnMapaJugadory = jugador->posEnY() / mapa.getLadoCelda();
    std::vector<int> posiciones;
    posiciones.push_back(posEnMapaJugadorx);
    posiciones.push_back(posEnMapaJugadory);
    return posiciones;
}
