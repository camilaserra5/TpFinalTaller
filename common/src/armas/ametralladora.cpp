#include "armas/ametralladora.h"

#define BALAS_POR_RAFAGA 5


void Ametralladora::atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) {
    int cantidad_balas = this->cantidad_rafagas * BALAS_POR_RAFAGA;
    jugador->gastarBalas(cantidad_balas);
    srand(time(NULL));
    int idJugadorMasCercano = JugadorAMenorDistancia(jugador, jugadores);
    if (idJugadorMasCercano != NO_HAY_JUGADOR_CERCANO) {
        for (int i = 0; i < cantidad_balas; i++) {
            //distancia influye en el danio y lode la precision
            int danio = (rand() % DANIO_MAX) + 1;
            danio = -danio;
            jugadores.at(idJugadorMasCercano)->actualizar_vida(danio);
        }
    }
}

void Ametralladora::obtenerBeneficio(ContenedorDeElementos& contenedor, Jugador *jugador) {
    if (!jugador->poseeArma(this)) {
        jugador->agregar_arma(this);
        // sacar arma del mapa;
    }

}
