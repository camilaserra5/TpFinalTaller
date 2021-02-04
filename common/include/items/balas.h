#ifndef BALAS_H
#define BALAS_H

#define BALAS 5

#include "item.h"

class Balas : public Item {
public:
    Balas(Posicion &posicion, int cantidad, int id);

    ~Balas();

    bool obtenerBeneficio(Jugador *jugador) override;

    Type getTipo() override;

private:
    int cant_balas;
};

#endif
