#include "armas/pistola.h"
#include <ctime>

#define DISTANCIA_MAX 2000000
#define BALAS_POR_RAFAGA 1

Pistola::Pistola(int cantidad_rafagas) :
        Arma(DISTANCIA_MAX, 4),
        precision(10),
        probalidad_acierto(10),
        cantidad_rafagas(cantidad_rafagas) {}

Pistola::~Pistola() {}

// conviene mandarle coordenadas de yo jugador??
// or ahora devuelve danio de ataque
void Pistola::atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) {
    srand(time(NULL));
    int idJugadorMasCercano = JugadorAMenorDistancia(jugador, jugadores);
    if (idJugadorMasCercano != NO_HAY_JUGADOR_CERCANO) {
        int cantidad_balas = this->cantidad_rafagas * BALAS_POR_RAFAGA;
        int i = 0;
        bool jugadorMurio = false;
        Jugador *jugadorAtacado = jugadores.at(idJugadorMasCercano);
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
    }
}

bool Pistola::esPistola() {
    return true;
}
