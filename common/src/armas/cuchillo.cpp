#include "armas/cuchillo.h"

#define DISTANCIA_ACUCHILLABLE 0.5 /*metros*/
#define DISTANCIA_MAX 1
#define NO_HAY_JUGADOR_CERCANO -1


Cuchillo::Cuchillo() :
        danio(10),
        Arma(DISTANCIA_ACUCHILLABLE, 3) {}

Cuchillo::~Cuchillo() {}

void Cuchillo::atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) {
    srand(time(NULL));
    int idJugadorMasCercano = JugadorAMenorDistancia(jugador, jugadores);
    Jugador *jugadorAtacado = jugadores.at(idJugadorMasCercano);
    if (idJugadorMasCercano != NO_HAY_JUGADOR_CERCANO) {
        int danio = (rand() % DANIO_MAX) + 1;
        danio = -danio;
        jugadorAtacado->actualizar_vida(danio);
        if (jugadorAtacado->estaMuerto()) {
            jugador->aniadirEnemigosMatados(1);
        }
    }
}

Type Cuchillo::getTipo(){
    return  ObjetosJuego::obtenerTipoPorNombre("cuchillo");
}
