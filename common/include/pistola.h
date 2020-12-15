#ifndef _PISTOLA_H
#define _PISTOLA_H

#include "arma.h"


class Pistola : public Arma {
public:
    Pistola(int cantidad_rafagas);

    ~Pistola();

    void atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) override;

private:
    int precision;
    int probalidad_acierto;
    int cantidad_rafagas;
};

#endif
