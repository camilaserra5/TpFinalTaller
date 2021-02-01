#ifndef __PUERTA__H
#define __PUERTA__H

#include "posicion.h"

class Puerta{
    private:
      bool abierta;
      bool necesitaLlave;
      Posicion posicion;//es el punto medio de la puerta, siempre va a estar en y = 0 o x = 0
    public:
      Puerta();
      ~Puerta();
      void abrir();
      void cerrar();
      bool puedeSerAbierta(Posicion& posicionJugador,bool jugadorTieneLlave);
};

#endif
