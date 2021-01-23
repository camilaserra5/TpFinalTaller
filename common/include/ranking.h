#ifndef RANKING_H
#define RANKING_H

class Ranking{

public:
  /*devuelve el top cantidadJugadores de los jugadores post partida en orden de mejor a peor*/
  std::vector<int> jugadores obtenerTopJugadores(int cantidadTopJugadores,std::map<int, Jugador *> &jugadores);
};

#endif
