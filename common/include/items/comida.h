#ifndef COMIDA_H
#define COMIDA_H

#include "item.h"

class Comida : public Item {
public:
    Comida(Posicion &posicion);

    ~Comida();

    void obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) override;



private:
    int puntos_de_vida;
};

#endif
