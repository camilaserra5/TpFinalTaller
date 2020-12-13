#ifndef COMIDA_H
#define COMIDA_H
#include "item.h"

class Comida: public Item{
  public:
    Comida();
    ~Comida();
    void obtenerBeneficio(Jugador &jugador) override;
  private:
    int puntos_de_vida;
};

#endif
