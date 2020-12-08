#ifndef ATAQUE_H
#define ATAQUE_H
#include "comando.h"

class Ataque: public Comando{
  public:
    Ataque(){}
    ~Ataque(){}
    void estrategia() override;
  private:
    int ataque_asociado = 1;
    int destinox = 1;
    int destinoy = 1;
    int danio = 1;
};

#endif
