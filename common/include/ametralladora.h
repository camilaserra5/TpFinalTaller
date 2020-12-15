#ifndef AMETRALLADORA_H
#define AMETRALLADORA_H
#define DISTANCIA_MAX 2000000

#include "arma.h"

class Ametralladora : public Arma {
public:
    Ametralladora() : Arma(DISTANCIA_MAX) {}

    ~Ametralladora() {}

    void atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) override;

private:
    int cantidad_rafagas;
};

#endif
