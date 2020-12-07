#ifndef ATAQUE_H
#define ATAQUE_H
#include "comando.h"

class Ataque: public Comando{
  public:
    Ataque(){}
    void estrategia() override;
  private:
    int ataque_asociado;
};

#endif
