#ifndef SANGRE_H
#define SANGRE_H

#include "item.h"

class Sangre : public Item {
public:
    Sangre(Posicion &posicion, int id);

    ~Sangre();

    bool obtenerBeneficio(Jugador *jugador) override;

    Type getTipo() override;

private:
    int puntos_de_vida;
};

#endif
