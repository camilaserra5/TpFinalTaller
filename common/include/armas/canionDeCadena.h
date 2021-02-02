#ifndef CANION_DE_CADENA_H
#define CANION_DE_CADENA_H
#define DISTANCIA_MAX 2000000
#define TICKS_DISPARO_CANION (10/3)*0.03
#include "arma.h"
#include "items/item.h"

class CanionDeCadena : public Arma, public Item {
public:
    CanionDeCadena(Posicion &posicion, int id) : Arma(DISTANCIA_MAX, 2), Item(posicion, id),
                  contador(TICKS_DISPARO_CANION){}

    ~CanionDeCadena() {}

    void atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) override;

    void obtenerBeneficio(ContenedorDeElementos &conteneor, Jugador *jugador);

    void atacarEfectivamente(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores);

    bool esPistola() override;

    Type getTipo() override;

private:
    int cantidad_rafagas;
    double contador;
};

#endif
