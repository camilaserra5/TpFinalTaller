#include "armas/pistola.h"
#include "../include/actualizaciones/actualizacionAtaque.h"

#define DISTANCIA_MAX 2000000
#define BALAS_POR_RAFAGA 1

Pistola::Pistola(ConfiguracionPartida& configuracion) :
        Arma(DISTANCIA_MAX, 4,configuracion.getDanioMaximoArma()),
        configuracion(configuracion) {}

Pistola::~Pistola() {}

Type Pistola::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("pistola");
}


Actualizacion *Pistola::atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) {
    srand(time(NULL));
    std::map<int, Jugador *> jugadoresAtacados;
    int idJugadorMasCercano = JugadorAMenorDistancia(jugador, jugadores);
    if (idJugadorMasCercano != NO_HAY_JUGADOR_CERCANO && jugador->cantidad_balas() > 0) {
        int cantidad_balas = configuracion.getBalasPorRafagaPistola();
        int i = 0;
        bool jugadorMurio = false;
        Jugador *jugadorAtacado = jugadores.at(idJugadorMasCercano);
        while (i < cantidad_balas && !jugadorMurio) {
            //distancia influye en el danio y lode la precision
            int danio = (rand() % configuracion.getDanioMaximoArma()) + 1;
            danio = -danio;
            jugadorAtacado->actualizar_vida(danio);
            if (jugadorAtacado->estaMuerto()) {
                jugadorMurio = true;
                jugador->aniadirEnemigosMatados(1);
            }
            i++;
        }
        jugadoresAtacados.insert({jugadorAtacado->getId(), jugadorAtacado});
    }
    jugador->gastarBalas(configuracion.getBalasPorRafagaPistola());
    jugador->actualizarArma();
    return new ActualizacionAtaque(jugador, jugadoresAtacados);

}
