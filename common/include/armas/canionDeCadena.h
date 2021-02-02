#ifndef CANION_DE_CADENA_H
#define CANION_DE_CADENA_H
#define DISTANCIA_MAX 2000000

#include "arma.h"
#include "items/item.h"

class CanionDeCadena : public Arma, public Item {
public:
    CanionDeCadena(Posicion &posicion, int id) : Arma(DISTANCIA_MAX, 2), Item(posicion, id) {}

    ~CanionDeCadena() {}

    void atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) override;

    bool obtenerBeneficio(Jugador *jugador);

    Type getTipo() override;

private:
    int cantidad_rafagas;
};

#endif
