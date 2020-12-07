#ifndef MOVIMENTO_H
#define MOVIMIENTO_H
#include "comando.h"

class ItemTomado: public Comando{
  private:
    int item = 1;
  public:
    ItemTomado() {}
    void estrategia() override;
};

#endif
