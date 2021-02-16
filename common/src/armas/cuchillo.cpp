#include "armas/cuchillo.h"
#include "../include/actualizaciones/actualizacionAtaque.h"
#define DISTANCIA_ACUCHILLABLE 0.5 /*metros*/
#define DISTANCIA_MAX 1
#define NO_HAY_JUGADOR_CERCANO -1


Cuchillo::Cuchillo() :Arma(DISTANCIA_ACUCHILLABLE, 3), danio(10){}

Cuchillo::~Cuchillo() {}

Actualizacion* Cuchillo::atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) {
    srand(time(NULL));
    int idJugadorMasCercano = JugadorAMenorDistancia(jugador, jugadores);
    std::map<int, Jugador*> jugadoresAtacados;
    Jugador *jugadorAtacado = jugadores.at(idJugadorMasCercano);
    if (idJugadorMasCercano != NO_HAY_JUGADOR_CERCANO) {
        int danio = (rand() % DANIO_MAX) + 1;
        danio = -danio;
        jugadorAtacado->actualizar_vida(danio);
        if (jugadorAtacado->estaMuerto()) {
            jugador->aniadirEnemigosMatados(1);
        }
        jugadoresAtacados.insert({idJugadorMasCercano,jugadorAtacado});
    }
    jugador->dejarDeDisparar();
    return new ActualizacionAtaque(jugador, jugadoresAtacados);
}

Type Cuchillo::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("cuchillo");
}
