#include "armas/cuchillo.h"
#include "../include/actualizaciones/actualizacionAtaque.h"

#define DISTANCIA_ACUCHILLABLE 100 /*metros*/
#define DISTANCIA_MAX 1
#define NO_HAY_JUGADOR_CERCANO -1


Cuchillo::Cuchillo(ConfiguracionPartida& configuracion) : Arma(DISTANCIA_ACUCHILLABLE, 3, configuracion.getDanioMaximoArma()),
configuracion(configuracion)  {}

Cuchillo::~Cuchillo() {}

Cuchillo::Cuchillo():Arma(ID_CUCHILLO) {}

Actualizacion *Cuchillo::atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) {
    srand(time(NULL));
    int idJugadorMasCercano = JugadorAMenorDistancia(jugador, jugadores);
    std::map<int, Jugador *> jugadoresAtacados;
    if (idJugadorMasCercano != NO_HAY_JUGADOR_CERCANO) {
        Jugador *jugadorAtacado = jugadores.at(idJugadorMasCercano);
        int danio = (rand() % configuracion.getDanioMaximoArma()) + 1;
        danio = -danio;
        jugadorAtacado->actualizar_vida(danio);
        if (jugadorAtacado->estaMuerto()) {
            jugador->aniadirEnemigosMatados(1);
        }
        jugadoresAtacados.insert({idJugadorMasCercano, jugadorAtacado});
    }
    return new ActualizacionAtaque(jugador, jugadoresAtacados);
}

Type Cuchillo::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("cuchillo");
}
