#ifndef RANKING_H
#define RANKING_H

#include <vector>
#include "jugador.h"
#include <map>

class Ranking{

public:
  /*devuelve el top cantidadJugadores de los jugadores post partida en orden de mejor a peor*/
  std::vector<int> obtenerTopJugadores(int cantidadTopJugadores,std::map<int, Jugador *> &jugadores);
};

#endif
