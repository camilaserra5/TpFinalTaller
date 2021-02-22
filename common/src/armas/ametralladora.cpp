#include "armas/ametralladora.h"


#include "../include/actualizaciones/actualizacionAtaque.h"


Ametralladora::Ametralladora(Posicion &posicion, int id, ConfiguracionPartida& configuracion) :
        Arma(DISTANCIA_MAX, 1,configuracion.getDanioMaximoArma()),
        Item(posicion, id),
        contador(TICKS_DISPARO_AMETRALLADORA),
        configuracion(configuracion) {}

Ametralladora::~Ametralladora() {}

Actualizacion *
Ametralladora::atacarEfectivamente(Jugador *jugador, std::map<int, Jugador *> &jugadores) {
    int cantidad_balas = configuracion.getBalasPorRafagaAmetralladora();
    jugador->gastarBalas(cantidad_balas);
    srand(time(NULL));
    int idJugadorMasCercano = JugadorAMenorDistancia(jugador, jugadores);
    std::map<int, Jugador *> jugadoresAtacados;
    if (idJugadorMasCercano != NO_HAY_JUGADOR_CERCANO) {
        int i = 0;
        bool jugadorMurio = false;
        Jugador *jugadorAtacado = jugadores.at(idJugadorMasCercano);
        while (i < cantidad_balas && !jugadorMurio) {
            //distancia influye en el danio y lode la precision
            //  int danioPorDistancia = 1 / (jugador->distanciaA(jugadorAtacado));
            int danio = (rand() % configuracion.getDanioMaximoArma()) + 1;
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
    jugador->gastarBalas(configuracion.getBalasPorRafagaAmetralladora());
    jugador->actualizarArma();
    return new ActualizacionAtaque(jugador, jugadoresAtacados);
}

Actualizacion *Ametralladora::atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) {
    int balasJugador = jugador->cantidad_balas();
    if (this->contador == 0 && balasJugador > configuracion.getBalasPorRafagaAmetralladora()) {
        this->contador = TICKS_DISPARO_AMETRALLADORA;
        return this->atacarEfectivamente(jugador, jugadores);
    } else {
        this->contador--; // consultar
        return NULL;
    }

}

bool Ametralladora::obtenerBeneficio(Jugador *jugador) {
    if (!jugador->poseeArma(this)) {
        jugador->agregar_arma(this);
        return true;
    }
    return false;
}

Type Ametralladora::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("ametralladora");
}
