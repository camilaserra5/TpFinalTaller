#ifndef __PUERTA__H
#define __PUERTA__H

#include "posicion.h"

class Puerta{
    private:
      bool abierta;
      bool necesitaLlave;
      Posicion posicion;//es el punto medio de la puerta, siempre va a estar en y = 0 o x = 0
    public:
      Puerta(bool necesitaLlave,Posicion& posicion): abierta(false),necesitaLlave(necesitaLlave),posicion(posicion){}
      ~Puerta(){}
      void abrir();
      void cerrar();
      bool puedeSerAbierta(bool jugadorTieneLlave,double& distancia) const;
      double distanciaA(Posicion& posicion);
};

#endif
