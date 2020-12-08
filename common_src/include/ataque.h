#ifndef ATAQUE_H
#define ATAQUE_H
#include "comando.h"

class Ataque: public Comando{
    private:
      int ataque_asociado;
      int destinox;
      int destinoy;
      int danio;
  public:
    Ataque(){}
    ~Ataque(){}
    void estrategia() override{
      std::cout << "ataco pium pium\n";
    }
};

#endif
