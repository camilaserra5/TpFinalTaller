#ifndef AMETRALLADORA_H
#define AMETRALLADORA_H
#define DISTANCIA_MAX 2000000
#define TICKS_DISPARO_AMETRALLADORA  10

#include "arma.h"
#include "items/item.h"

class Ametralladora : public Arma, public Item {
public:
    Ametralladora(Posicion &posicion, int id);

    ~Ametralladora();

    void atacar(int distancia_a_pared, Jugador *jugador,
                std::map<int, Jugador *> &jugadores) override;

    bool obtenerBeneficio(Jugador *jugador) override;

    void atacarEfectivamente(int distancia_a_pared, Jugador *jugador,
                             std::map<int, Jugador *> &jugadores);

    Type getTipo() override;


private:
    double contador;
};

#endif
