#ifndef COMIDA_H
#define COMIDA_H

#include "item.h"

class Comida : public Item {
public:
    Comida(Posicion &posicion, int id);

    ~Comida();

    void obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) override;

    Type getTipo() override;
    
private:
    int puntos_de_vida;
};

#endif
