#ifndef ACTUALIZACION_H
#define ACTUALIZACION_H
#include "estadoJuego.h"

class Actualizacion {
  public:
    Actualizacion(EstadoJuego &estadoJuego):
    estadoJuego(estadoJuego){}
  private:
    EstadoJuego &estadoJuego;
};

#endif
