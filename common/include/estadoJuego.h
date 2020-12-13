#ifndef _ESTADOJUEGO_H
#define _ESTADOJUEGO_H

#include "map.h"
#include "jugador.h"
#include <map>

class EstadoJuego {
public:
    EstadoJuego(Map &mapa, std::map<int, Jugador> &jugadores);

    ~EstadoJuego();

    void moverse_a_derecha(int idJugador);

    void moverse_a_izquierda(int idJugador);

    void moverse_arriba(int idJugador);

    void moverse_abajo(int idJugador);

    void no_me_muevo(int idJugador);

private:
    Map &mapa;
    std::map<int, Jugador> &jugadores;
};

#endif
