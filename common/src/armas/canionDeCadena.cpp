#include "armas/canionDeCadena.h"

#define DISTANCIA_MAX 2000000

#define BALAS_POR_RAFAGA 1

void CanionDeCadena::atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) {
    srand(time(NULL));
    int idJugadorMasCercano = JugadorAMenorDistancia(jugador, jugadores);
    if (idJugadorMasCercano != NO_HAY_JUGADOR_CERCANO) {
        int cantidad_balas = this->cantidad_rafagas * BALAS_POR_RAFAGA;
        for (int i = 0; i < cantidad_balas; i++) {
            //distancia influye en el danio y lode la precision
            int danio = (rand() % DANIO_MAX) + 1;
            danio = -danio;
            jugadores.at(idJugadorMasCercano)->actualizar_vida(danio);
            //sleep(0.1);//chequear
        }
    }
}


void CanionDeCadena::obtenerBeneficio(Jugador* jugador){
      if (!jugador->poseeArma(this)){
            jugador->agregar_arma(this);
            //sacar el arma del juego;
      }
}
