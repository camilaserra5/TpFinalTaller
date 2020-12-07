#ifndef MOVIMENTO_H
#define MOVIMIENTO_H
#include "comando.h"

class Movimiento: public Comando{
  private:
    int tecla_asociada = 1;
  public:
    Movimiento() {}
    void estrategia() override;
};
#endif
