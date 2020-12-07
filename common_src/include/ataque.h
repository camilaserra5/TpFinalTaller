#ifndef ATAQUE_H
#define ATAQUE_H
#include "comando.h"

class Ataque: public Comando{
  public:
    Ataque(int &destinox, int &destinoy);
    ~Ataque();
    void estrategia() override;
  private:
    int ataque_asociado;
    int destinox;
    int destinoy;
    int danio;
};

#endif
