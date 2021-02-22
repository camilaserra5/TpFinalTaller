#include "../include/procesadorDeActualizaciones.h"
#include "../include/modelo.h"
#include "../include/player.h"

void ProcesadorDeActualizaciones::procesarActualizacionEmpezoPartida() {
    Player &player = this->modelo->getPlayer();
    auto inicio = (ActualizacionInicioPartida *) actualizacion;
    EstadoJuego &estadoJuego = inicio->obtenerEstadoJuego();
    std::map<int, Jugador *> &jugadores = estadoJuego.obtenerJugadores();
    std::map<int, Jugador *>::iterator it;
    Jugador *jugador = jugadores.at(player.getId());

    int vida = jugador->puntos_de_vida();
    int posx = jugador->getPosicion().pixelesEnX();
    int posy = jugador->getPosicion().pixelesEnY();
    int angulo = jugador->getAnguloDeVista();
    int idArma = jugador->getArma()->getId();
    int puntaje = jugador->obtenerPuntosTotales();
    bool disparando = jugador->estaDisparando();
    int cantVidas = jugador->cant_de_vida();
    int balas = jugador->cantidad_balas();
    this->modelo->actualizarJugador(posx, posy, vida, angulo, idArma,
                                    disparando, puntaje, cantVidas, balas);
    for (it = jugadores.begin(); it != jugadores.end(); it++) {
        if (it->second->getId() != player.getId()) {
            int idE = it->first;
            int vidaE = it->second->puntos_de_vida();
            int posxE = it->second->getPosicion().pixelesEnX();
            int posyE = it->second->getPosicion().pixelesEnY();
            int idArmaE = idArma;
            int anguloJugador = angulo;
            int anguloE = it->second->getAnguloDeVista();
            bool disparandoE = it->second->estaDisparando();
            int puntajeE = it->second->obtenerPuntosTotales();
            this->modelo->actualizarEnemigo(idE, vidaE, disparandoE, posxE,
                                            posyE, idArmaE, anguloJugador,
                                            anguloE, puntajeE);
        }
    }

    Map& mapa = estadoJuego.obtenerMapa();
    mapa.setLadoCelda(ANCHO_CANVAS);
    std::vector<Item *> items = mapa.obtenerItems();
    int cantItems = items.size();
    for (int i = 0; i < cantItems; i++) {
        Item *item = items[i];
        int idI = item->getId();
        Type tipo = item->getTipo();
        int posxI = item->obtenerPosicion().pixelesEnX();
        int posyI = item->obtenerPosicion().pixelesEnY();
        this->modelo->actualizarObjeto(idI, tipo, posxI, posyI);
    }
    this->modelo->setMapa(std::move(mapa));
}

void ProcesadorDeActualizaciones::procesarActualizacionAperturaDePuerta() {
//    auto apertura = (ActualizacionAperturaPuerta *) actualizacion;
}

void ProcesadorDeActualizaciones::procesarActualizacionCambioDeArma() {
    Player &player = this->modelo->getPlayer();
    auto cambioArma = (ActualizacionCambioArma *) actualizacion;
    int idJugador = cambioArma->obtenerIdJugador();
    if (idJugador == player.getId()) {
        this->modelo->actualizarArmaJugador(cambioArma->obtenerIdArma());
        this->modelo->actualizarArmaEnemigos(cambioArma->obtenerIdArma());
    }
}

void ProcesadorDeActualizaciones::procesarActualizacionAtaque() {
    Player &player = this->modelo->getPlayer();
    auto ataque = (ActualizacionAtaque *) actualizacion;
    Jugador *jugadorAux = ataque->obtenerJugador();
    if (jugadorAux->getId() == player.getId()) {
        this->modelo->actualizarEstadoAtaqueJugador(jugadorAux->puntos_de_vida(), jugadorAux->getArma()->getId(),
                                                    jugadorAux->cantidad_balas(),
                                                    jugadorAux->obtenerPuntosTotales(), jugadorAux->cant_de_vida(),
                                                    jugadorAux->estaDisparando());
    }
    std::map<int, Jugador *> &jugadoresAtacados = ataque->obtenerJugadoresAtacados();
    std::map<int, Jugador *>::iterator it;
    for (it = jugadoresAtacados.begin(); it != jugadoresAtacados.end(); it++) {
        if (it->first == player.getId()) {
            this->modelo->actualizarEstadoAtaqueJugador(it->second->puntos_de_vida(), it->second->getArma()->getId(),
                                                        it->second->cantidad_balas(),
                                                        it->second->obtenerPuntosTotales(), it->second->cant_de_vida(),
                                                        it->second->estaDisparando());
        } else {
            int idE = it->first;
            int vidaE = it->second->puntos_de_vida();
            this->modelo->actualizarVidaEnemigo(idE, vidaE, jugadorAux->getArma()->getId());
            this->modelo->actualizarPosicionEnemigo(idE, ataque->obtenerJugador()->posEnX(),
                                                    ataque->obtenerJugador()->posEnY(),
                                                    ataque->obtenerJugador()->getAnguloDeVista());
        }
    }
}

void ProcesadorDeActualizaciones::procesarActualizacionMoverse() {
    Player &player = this->modelo->getPlayer();
    auto movimiento = (ActualizacionMovimiento *) actualizacion;
    int idJugador = movimiento->obtenerJugador().getId();
    if (idJugador == player.getId()) {
        this->modelo->actualizarPosicionJugador(movimiento->obtenerJugador().posEnX(),
                                                movimiento->obtenerJugador().posEnY(),
                                                movimiento->obtenerJugador().getAnguloDeVista());
    } else {
        this->modelo->actualizarPosicionEnemigo(idJugador, movimiento->obtenerJugador().posEnX(),
                                                movimiento->obtenerJugador().posEnY(),
                                                movimiento->obtenerJugador().getAnguloDeVista());
    }
}

void ProcesadorDeActualizaciones::procesarActualizacionAgarreItem() {
    std::cerr << "proceso agarro itemm" << std::endl;
    Player &player = this->modelo->getPlayer();
    auto agarroItem = (ActualizacionAgarroItem *) actualizacion;
    int idJugador = agarroItem->obtenerJugador()->getId();
    Item *item = agarroItem->obtenerItem();
    int idItem = item->getId();
    Jugador *jugador = agarroItem->obtenerJugador();
    this->modelo->sacarItem(idItem);
    if (idJugador == player.getId()) {
        this->modelo->actualizarBeneficioJugador(jugador->puntos_de_vida(),
                                                 jugador->cantidad_balas(),
                                                 jugador->obtenerPuntosTotales(),
                                                 jugador->cant_de_vida());
    }
}

void ProcesadorDeActualizaciones::procesarActualizacionAgregarItem() {
    auto agregoItem = (ActualizacionAgregarItem *) actualizacion;
    Item *item = agregoItem->obtenerItem();
    int idI = item->getId();
    Type tipo = item->getTipo();
    int posxI = item->obtenerPosicion().pixelesEnX();
    int posyI = item->obtenerPosicion().pixelesEnY();
    this->modelo->actualizarObjeto(idI, tipo, posxI, posyI);
}

void ProcesadorDeActualizaciones::procesarActualizacionTerminoPartida() {
    auto termino = (ActualizacionTerminoPartida *) actualizacion;
    Ranking *ranking = new Ranking(std::move(termino->obtenerJugadores()));
    this->modelo->terminoPartida(*ranking);
}

void ProcesadorDeActualizaciones::ejecutar() {
    int idActualizacion = actualizacion->obtenerId();
    if (idActualizacion == static_cast<int>(Accion::empezoPartida)) {
        procesarActualizacionEmpezoPartida();
    } else if (idActualizacion == static_cast<int>(Accion::aperturaDePuerta)) {
        procesarActualizacionAperturaDePuerta();
    } else if (idActualizacion == static_cast<int>(Accion::cambioDeArma)) {
        procesarActualizacionCambioDeArma();
    } else if (idActualizacion == static_cast<int>(Accion::ataque)) {
        procesarActualizacionAtaque();
    } else if (idActualizacion == static_cast<int>(Accion::moverse)) {
        procesarActualizacionMoverse();
    } else if (idActualizacion == static_cast<int>(Accion::agarreItem)) {
        procesarActualizacionAgarreItem();
    } else if (idActualizacion == static_cast<int>(Accion::agregarItem)) {
        procesarActualizacionAgregarItem();
    } else if (idActualizacion == static_cast<int>(Accion::terminoPartida)) {
        procesarActualizacionTerminoPartida();
    }
}
