#include "armas/cuchillo.h"
#include "../include/actualizaciones/actualizacionAtaque.h"

#define DISTANCIA_ACUCHILLABLE 20 /*metros*/
#define DISTANCIA_MAX 1
#define NO_HAY_JUGADOR_CERCANO -1


Cuchillo::Cuchillo() : Arma(DISTANCIA_ACUCHILLABLE, 3), danio(10) {}

Cuchillo::~Cuchillo() {}

Actualizacion *Cuchillo::atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) {
    std::cerr << "ataque con cuchiiii\ns";

    srand(time(NULL));
    std::cerr << "ataco con cuchillo\n";
    int idJugadorMasCercano = JugadorAMenorDistancia(jugador, jugadores);
    std::map<int, Jugador *> jugadoresAtacados;
    std::cerr << "juagdor a atacar: " << idJugadorMasCercano;
    if (idJugadorMasCercano != NO_HAY_JUGADOR_CERCANO) {
        Jugador *jugadorAtacado = jugadores.at(idJugadorMasCercano);
        std::cerr << "ACUCHILLO con distancia: " << jugadorAtacado->getPosicion().distanciaA(jugador->getPosicion());
        std::cerr << "ACUCHILLO\n";
        int danio = (rand() % DANIO_MAX) + 1;
        danio = -danio;
        jugadorAtacado->actualizar_vida(danio);
        if (jugadorAtacado->estaMuerto()) {
            jugador->aniadirEnemigosMatados(1);
            std::cerr << "MURIO JUGADOR ACUCHILLADO\n";
        }
        jugadoresAtacados.insert({idJugadorMasCercano, jugadorAtacado});
    }
    return new ActualizacionAtaque(jugador, jugadoresAtacados);
}

Type Cuchillo::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("cuchillo");
}
