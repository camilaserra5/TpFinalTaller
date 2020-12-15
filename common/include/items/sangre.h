#ifndef SANGRE_H
#define SANGRE_H

#include "item.h"

class Sangre : public Item {
public:
    Sangre();

    ~Sangre();

    void obtenerBeneficio(Jugador *jugador) override;

private:
    int puntos_de_vida;
};

#endif
