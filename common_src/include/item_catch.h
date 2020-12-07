#ifndef MOVIMENTO_H
#define MOVIMIENTO_H
#include "comando.h"

class Item_catch: public Comando{
  private:
    int item = 1;
  public:
    Item_catch() {}
    void estrategia() override;
};

#endif
