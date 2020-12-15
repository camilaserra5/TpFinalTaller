#ifndef CANION_DE_CADENA_H
#define CANION_DE_CADENA_H
#define DISTANCIA_MAX 2000000
#include "arma.h"

class CanionDeCadena: public Arma{
  public:
    CanionDeCadena(): Arma(DISTANCIA_MAX){}
    ~CanionDeCadena(){}
    void atacar(int distancia_a_pared,Jugador *jugador,std::map<int,Jugador*> &jugadores) override;
  private:
    int cantidad_rafagas;
};

#endif
