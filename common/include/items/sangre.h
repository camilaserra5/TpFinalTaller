#ifndef SANGRE_H
#define SANGRE_H

#include "item.h"

class Sangre : public Item {
public:
    Sangre(Posicion &posicion, int id);

    ~Sangre();

    void obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) override;

    Type getTipo() override;

private:
    int puntos_de_vida;
};

#endif
