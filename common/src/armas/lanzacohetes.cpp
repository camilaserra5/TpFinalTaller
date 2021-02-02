#include "../include/armas/lanzacohetes.h"
#include <math.h>
#include <iterator>

#define RADIO_DE_IMPACTO 10
#define BALAS_POR_LANZACOHETES 5

void verificarJugadoresEnRango(Posicion &posicionImpacto, std::map<int, Jugador *> &jugadores, Jugador *jugador) {
    std::map<int, Jugador *>::iterator it;
    int jugadoresMatados = 0;
    for (it = jugadores.begin(); it != jugadores.end(); ++it) {
        if (posicionImpacto.distanciaA(it->second->getPosicion()) < RADIO_DE_IMPACTO) {
            int danio = -DANIO_MAX;//por ahora
            it->second->actualizar_vida(danio);
            if (it->second->estaMuerto()) {
                jugadoresMatados++;
            }
        }
    }
    jugador->aniadirEnemigosMatados(jugadoresMatados);
}

void LanzaCohetes::atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) {
    /*no cheqyeo las balas porque si no tiene 5 no podria tener un lanzacohetes*/
    jugador->gastarBalas(BALAS_POR_LANZACOHETES);
    int idJugadorMasCercano = JugadorAMenorDistancia(jugador, jugadores);

    if (idJugadorMasCercano != NO_HAY_JUGADOR_CERCANO) {
        verificarJugadoresEnRango(jugadores.at(idJugadorMasCercano)->getPosicion(), jugadores, jugador);
    } else {
        int xPared = floor(distancia_a_pared * cos(jugador->getAnguloDeVista()));
        int yPared = floor(distancia_a_pared * sin(jugador->getAnguloDeVista()));
        Posicion posPared(xPared, yPared, 0);
        verificarJugadoresEnRango(posPared, jugadores, jugador);
    }
    jugador->actualizarArma();
}

bool LanzaCohetes::obtenerBeneficio(Jugador *jugador) {
    if (!jugador->poseeArma(this)) {
        jugador->agregar_arma(this);
        // sacar arma del mapa;
    }

}

Type LanzaCohetes::getTipo(){
    return Type::lanzaCohetes;
}
