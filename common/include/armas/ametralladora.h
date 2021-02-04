#ifndef AMETRALLADORA_H
#define AMETRALLADORA_H
#define DISTANCIA_MAX 2000000
#define TICKS_DISPARO_AMETRALLADORA  10

#include "arma.h"
#include "items/item.h"

class Ametralladora : public Arma, public Item {
public:
    Ametralladora(Posicion &posicion, int id) : Arma(DISTANCIA_MAX, 1), Item(posicion, id), contador(TICKS_DISPARO_AMETRALLADORA) {}

    ~Ametralladora() {}

    void atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) override;

    bool obtenerBeneficio(Jugador *jugador) override;

    void atacarEfectivamente(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores);

    Type getTipo() override;


private:
    int cantidad_rafagas;
    double contador;
};

#endif
