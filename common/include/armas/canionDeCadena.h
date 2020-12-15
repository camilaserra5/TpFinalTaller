#ifndef CANION_DE_CADENA_H
#define CANION_DE_CADENA_H
#define DISTANCIA_MAX 2000000

#include "arma.h"
#include "items/item.h"

class CanionDeCadena : public Arma , public Item{
public:
    CanionDeCadena() : Arma(DISTANCIA_MAX,2) {}

    ~CanionDeCadena() {}

    void atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) override;

    void obtenerBeneficio(Jugador* jugador);

private:
    int cantidad_rafagas;
};

#endif
