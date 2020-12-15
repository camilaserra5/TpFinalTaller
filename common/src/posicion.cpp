#include "../include/posicion.h"
#define DELTA_DISTANCIA 0.5
#include <math.h>

int Posicion::distanciaA(Posicion &posicion){
  float x = this->pixelesX - posicion.pixelesX;
  float y = this->pixelesY - posicion.pixelesY;
  return sqrt((x*x) + (y*y));
  }

bool Posicion::intersectaConMiAngulo(Posicion &otroJugador){
  int xFinal = this->pixelesX + 1;
  int yFinal = this->pixelesX * tan(this->anguloDeVista);
  float pendienteRecta = (yFinal - this->pixelesY) / (xFinal - this->pixelesX);
  int yOtroJugador = pendienteRecta * otroJugador.pixelesX + this->pixelesY;
  return (abs(yOtroJugador - otroJugador.pixelesY) <= DELTA_DISTANCIA);
}
