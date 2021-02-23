#include "../include/armas/lanzacohetes.h"
#include <math.h>
#include <iterator>
#include "../include/actualizaciones/actualizacionAtaque.h"

#define RADIO_DE_IMPACTO 10

LanzaCohetes::LanzaCohetes(Posicion &posicion, int id,ConfiguracionPartida& configuracion) :
        Arma(DISTANCIA_MAX, 5,configuracion.getDanioMaximoArma()), Item(posicion, id),
        configuracion(configuracion){}

LanzaCohetes::~LanzaCohetes() {}

std::map<int, Jugador *> LanzaCohetes::verificarJugadoresEnRango(Posicion &posicionImpacto,
                                                   std::map<int, Jugador *> &jugadores,
                                                   Jugador *jugador) {
    std::map<int, Jugador *>::iterator it;
    std::map<int, Jugador *> jugadoresAtacados;
    int jugadoresMatados = 0;
    for (it = jugadores.begin(); it != jugadores.end(); ++it) {
        if (posicionImpacto.distanciaA(it->second->getPosicion()) < RADIO_DE_IMPACTO) {
            int danio = -this->configuracion.getDanioMaximoArma();
            it->second->actualizar_vida(danio);
            jugadoresAtacados.insert({it->first, it->second});
            if (it->second->estaMuerto()) {
                jugadoresMatados++;
            }
        }
    }
    jugador->aniadirEnemigosMatados(jugadoresMatados);
    jugador->dejarDeDisparar();
    return jugadoresAtacados;
}

Actualizacion *LanzaCohetes::atacar(int distancia_a_pared, Jugador *jugador,
                                    std::map<int, Jugador *> &jugadores) {
    jugador->gastarBalas(configuracion.getBalasPorRafagaAmetralladora());
    int idJugadorMasCercano = JugadorAMenorDistancia(jugador, jugadores);
    std::map<int, Jugador *> jugadoresAtacados;
    if (idJugadorMasCercano != NO_HAY_JUGADOR_CERCANO) {
        jugadoresAtacados = verificarJugadoresEnRango(jugadores.at(idJugadorMasCercano)->getPosicion(), jugadores,
                                                      jugador);
    } else {
        int xPared = floor(distancia_a_pared * cos(jugador->getAnguloDeVista()));
        int yPared = floor(distancia_a_pared * sin(jugador->getAnguloDeVista()));
        Posicion posPared(xPared, yPared, 0);
        jugadoresAtacados = verificarJugadoresEnRango(posPared, jugadores, jugador);
    }
    jugador->gastarBalas(configuracion.getBalasPorRafagaAmetralladora());
    jugador->actualizarArma();
    return new ActualizacionAtaque(jugador, jugadoresAtacados);
}

bool LanzaCohetes::obtenerBeneficio(Jugador *jugador) {
    if (!jugador->poseeArma(this)) {
        jugador->agregar_arma(this);
        return true;
    }
    return false;
}

Type LanzaCohetes::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("lanzaCohetes");
}
