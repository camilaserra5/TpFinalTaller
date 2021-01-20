#ifndef SANGRE_H
#define SANGRE_H

#include "item.h"

class Sangre : public Item {
public:
    Sangre(Posicion &posicion);

    ~Sangre();

    void obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) override;

private:
    int puntos_de_vida;
};

#endif
