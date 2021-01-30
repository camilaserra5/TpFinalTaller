#ifndef _ARMA_H
#define _ARMA_H
#define NO_HAY_JUGADOR_CERCANO -1
#define DANIO_MAX 10

#define ID_CUCHILLO 3
#define ID_PISTOLA 4
#define ID_AMETRALLADORA 1
#define ID_LANZACOHETES 5
#define ID_CANION_DE_CADENA 2
#define BALAS_PARA_LANZACOHETES 5

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

    virtual bool esPistola() = 0;

    int getId();

protected:
    int distancia_max_atacable;

    int posicionAtacable(Posicion &atacante, Posicion &otroJugador);

    int id;

};

#endif
