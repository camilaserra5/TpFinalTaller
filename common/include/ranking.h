#ifndef RANKING_H
#define RANKING_H

#include <vector>
#include "jugador.h"
#include <map>

class Ranking {

public:
    Ranking(std::map<int, Jugador *> jugadores);

    /*devuelve el top cantidadJugadores de los jugadores post partida en orden de mejor a peor*/
    std::vector<int> obtenerTopJugadores(int cantidadTopJugadores);

    std::vector<std::pair<int, Jugador *>> obtenerTop5EnemigosMatados();

    std::vector<std::pair<int, Jugador *>> obtenerTop5PuntosTotalesPorTesoros();

    std::vector<std::pair<int, Jugador *>> obtenerTop5BalasDisparadas();

private:
    std::map<int, Jugador *> jugadores;
};

#endif
