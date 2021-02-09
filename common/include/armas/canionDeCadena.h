#ifndef CANION_DE_CADENA_H
#define CANION_DE_CADENA_H
#define DISTANCIA_MAX 2000000
#define TICKS_DISPARO_CANION 3

#include "arma.h"
#include "items/item.h"

class CanionDeCadena : public Arma, public Item {
public:
    CanionDeCadena(Posicion &posicion, int id);

    ~CanionDeCadena();

    void atacar(int distancia_a_pared, Jugador *jugador,
                std::map<int, Jugador *> &jugadores) override;

    bool obtenerBeneficio(Jugador *jugador);

    void atacarEfectivamente(int distancia_a_pared, Jugador *jugador,
                             std::map<int, Jugador *> &jugadores);

    Type getTipo() override;

private:
    double contador;
};

#endif
