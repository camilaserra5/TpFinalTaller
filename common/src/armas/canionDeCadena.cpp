#include "armas/canionDeCadena.h"
#include "../include/actualizaciones/actualizacionAtaque.h"

#define DISTANCIA_MAX 2000000


CanionDeCadena::CanionDeCadena(Posicion &posicion, int id, ConfiguracionPartida& configuracion) :
        Arma(DISTANCIA_MAX, 2, configuracion.getDanioMaximoArma()),
        Item(posicion, id),
        contador(TICKS_DISPARO_CANION),
        configuracion(configuracion)  {}

CanionDeCadena::~CanionDeCadena() {}

Actualizacion *CanionDeCadena::atacarEfectivamente(Jugador *jugador, std::map<int, Jugador *> &jugadores) {
    srand(time(NULL));
    int idJugadorMasCercano = JugadorAMenorDistancia(jugador, jugadores);
    std::map<int, Jugador *> jugadoresAtacados;
    if (idJugadorMasCercano != NO_HAY_JUGADOR_CERCANO) {
        int cantidad_balas = configuracion.getBalasPorRafagaCanion();
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
        jugadoresAtacados.insert({idJugadorMasCercano, jugadorAtacado});
    }
    jugador->gastarBalas(configuracion.getBalasPorRafagaCanion());
    jugador->actualizarArma();
    return new ActualizacionAtaque(jugador, jugadoresAtacados);
}

Actualizacion *CanionDeCadena::atacar(int distancia_a_pared, Jugador *jugador,
                                      std::map<int, Jugador *> &jugadores) {
    int balasJugador = jugador->cantidad_balas();
    if (this->contador == 0 && balasJugador > configuracion.getBalasPorRafagaCanion()) {
        this->contador = TICKS_DISPARO_CANION;
        return this->atacarEfectivamente(jugador, jugadores);
    } else {
        this->contador--;
        return NULL;
    }
}


bool CanionDeCadena::obtenerBeneficio(Jugador *jugador) {
    if (!jugador->poseeArma(this)) {
        jugador->agregar_arma(this);
        return true;
    }
    return false;
}

Type CanionDeCadena::getTipo() {
    return ObjetosJuego::obtenerTipoPorNombre("canionDeCadena");
}
