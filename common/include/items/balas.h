#ifndef BALAS_H
#define BALAS_H

#define BALAS 5

#include "item.h"

class Balas : public Item {
public:
    Balas(Posicion &posicion, int cantidad);

    ~Balas();

    void obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) override;

private:
    int cant_balas;
};

#endif
