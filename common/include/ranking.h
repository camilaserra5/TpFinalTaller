#ifndef RANKING_H
#define RANKING_H

#include <vector>
#include "jugador.h"
#include <map>

class Ranking {

public:
    /*
      * Creara la clase ranking dejandola valida para uso
    */
    Ranking(std::map<int, Jugador *> jugadores);

    /*
     * devuelve el top cantidadJugadores de los jugadores post partida
     * en orden de mejor a peor
    */
    std::vector<int> obtenerTopJugadores(int cantidadTopJugadores);
    /*
      * devuelve el top 5 con mayor muertes
    */
    std::vector<std::pair<int, Jugador *>> obtenerTop5EnemigosMatados();
    /*
      * devuelve el top 5 con mayor puntos por tesoros
    */
    std::vector<std::pair<int, Jugador *>> obtenerTop5PuntosTotalesPorTesoros();
    /*
      * devuelve el top 5 con mayor cant de balas disparadas
    */  
    std::vector<std::pair<int, Jugador *>> obtenerTop5BalasDisparadas();

private:
    std::map<int, Jugador *> jugadores;
};

#endif
