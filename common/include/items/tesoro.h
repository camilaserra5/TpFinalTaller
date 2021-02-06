#ifndef TESORO_H
#define TESORO_H


#include "item.h"

class Tesoro : public Item {
public:
    Tesoro(int id, Type tipo, int puntos, Posicion &posicion);

    ~Tesoro();

    bool obtenerBeneficio(Jugador *jugador) override;

    Type getTipo() override;

private:
    int puntos;
    Type tipo;
};

#endif
