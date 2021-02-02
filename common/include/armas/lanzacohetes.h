#ifndef _LANZA_COHETES_H
#define _LANZA_COHETES_H

#define DISTANCIA_MAX 2000000

#include "arma.h"
#include "items/item.h"

class LanzaCohetes : public Arma, public Item {
public:
    LanzaCohetes(Posicion &posicion, int id) : Arma(DISTANCIA_MAX, 5), Item(posicion, id) {}

    ~LanzaCohetes() {}

    void atacar(int distancia_a_pared, Jugador *jugador, std::map<int, Jugador *> &jugadores) override;

    void obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) override;

    bool esPistola() override;

    Type getTipo() override;

};

#endif
