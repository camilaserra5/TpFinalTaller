#ifndef _ARMA_H
#define _ARMA_H
#define NO_HAY_JUGADOR_CERCANO -1
#define DANIO_MAX 10

#include <map>
#include "jugador.h"
#include <ctime>
#include "posicion.h"

class Arma {
public:
    Arma(int distancia_max_atacable, int id) :
            distancia_max_atacable(distancia_max_atacable), id(id) {}

    virtual ~Arma() {}

    virtual void atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) = 0;

    /*devuelve el id*/
    int JugadorAMenorDistancia(Jugador *jugador, std::map<int, Jugador *> &jugadores);

    bool esIgual(Arma *arma);

protected:
    int distancia_max_atacable;

    int posicionAtacable(Posicion &atacante, Posicion &otroJugador);

    int id;

};

#endif
