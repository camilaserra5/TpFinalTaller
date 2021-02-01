#ifndef TESORO_H
#define TESORO_H


#include "item.h"

class Tesoro : public Item {
public:
    Tesoro(int id, int puntos, Posicion &posicion);

    ~Tesoro();

    void obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) override;


private:
    int puntos;
};

#endif
