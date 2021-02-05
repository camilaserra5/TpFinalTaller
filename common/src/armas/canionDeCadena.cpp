#include "armas/canionDeCadena.h"

#define DISTANCIA_MAX 2000000

#define BALAS_POR_RAFAGA 1

CanionDeCadena::CanionDeCadena(Posicion &posicion, int id):
        Arma(DISTANCIA_MAX, 2),
        Item(posicion, id),
        contador(TICKS_DISPARO_CANION){}

CanionDeCadena::~CanionDeCadena(){}
void CanionDeCadena::atacarEfectivamente(int distancia_a_pared,
                                        Jugador *jugador,
                                        std::map<int, Jugador *> &jugadores){
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
    jugador->actualizarArma();
    jugador->dejarDeDisparar();
}

void CanionDeCadena::atacar(int distancia_a_pared, Jugador *jugador,
                            std::map<int, Jugador *> &jugadores) {
    int balasJugador = jugador->cantidad_balas();
    if (this->contador == 0 && balasJugador > BALAS_POR_RAFAGA){
        this->atacarEfectivamente(distancia_a_pared, jugador, jugadores);
        this->contador = TICKS_DISPARO_CANION;
    } else {
        this->contador --;
    }
}


bool CanionDeCadena::obtenerBeneficio(Jugador *jugador) {
    if (!jugador->poseeArma(this)) {
        jugador->agregar_arma(this);
        return true;
    }
    return false;
}

Type CanionDeCadena::getTipo(){
    return  ObjetosJuego::obtenerTipoPorNombre("canionDeCadena");
}
