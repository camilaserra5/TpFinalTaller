#ifndef AMETRALLADORA_H
#define AMETRALLADORA_H
#define DISTANCIA_MAX 2000000

#include "arma.h"
#include "items/item.h"

class Ametralladora : public Arma, public Item {
public:
    Ametralladora(Posicion &posicion, int id) : Arma(DISTANCIA_MAX, 1), Item(posicion, id) {}

    ~Ametralladora() {}

    void atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) override;

    void obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) override;

    bool esPistola() override;


private:
    int cantidad_rafagas;
};

#endif
