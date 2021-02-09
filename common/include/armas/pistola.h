#ifndef _PISTOLA_H
#define _PISTOLA_H

#include "armas/arma.h"


class Pistola : public Arma {
public:
    Pistola();

    ~Pistola();

    void atacar(int distancia_a_pared, Jugador *jugador,
                std::map<int, Jugador *> &jugadores) override;

    Type getTipo() override;

private:
    int precision;
    int probalidad_acierto;
};

#endif
