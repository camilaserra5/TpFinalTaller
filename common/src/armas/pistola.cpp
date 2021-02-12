#include "armas/pistola.h"
#include <ctime>
#include "../include/actualizaciones/actualizacionAtaque.h"

#define DISTANCIA_MAX 2000000
#define BALAS_POR_RAFAGA 1

Pistola::Pistola() :
        Arma(DISTANCIA_MAX, 4),
        precision(10),
        probalidad_acierto(10) {}

Pistola::~Pistola() {}

Type Pistola::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("pistola");
}

// conviene mandarle coordenadas de yo jugador??
// or ahora devuelve danio de ataque
Actualizacion* Pistola::atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) {
    srand(time(NULL));
    std::map<int, Jugador*> jugadoresAtacados;
    int idJugadorMasCercano = JugadorAMenorDistancia(jugador, jugadores);
    if (idJugadorMasCercano != NO_HAY_JUGADOR_CERCANO) {
        int cantidad_balas = BALAS_POR_RAFAGA;
        int i = 0;
        bool jugadorMurio = false;
        Jugador *jugadorAtacado = jugadores.at(idJugadorMasCercano);
        std::cerr << "balas: " << cantidad_balas << "murio: " << jugadorMurio << "\n";
        while (i < cantidad_balas && !jugadorMurio) {
            //distancia influye en el danio y lode la precision
            int danio = (rand() % DANIO_MAX) + 1;
            danio = -danio;
            jugadorAtacado->actualizar_vida(danio);
            if (jugadorAtacado->estaMuerto()) {
                jugadorMurio = true;
                jugador->aniadirEnemigosMatados(1);
            }
            i++;
        }
        jugadoresAtacados.insert({idJugadorMasCercano, jugadorAtacado});
    }
    jugador->actualizarArma();
    return new ActualizacionAtaque(jugador, jugadoresAtacados);

}
