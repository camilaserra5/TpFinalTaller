#include "../include/posicion.h"
#define DELTA_DISTANCIA 0.5

int distanciaA(Posicion &posicion){
  float x = this.posicionX - posicion.posicionX;
  float y = this.posicionY - posicion.posicionY;
  return sqrt((x*x) + (y*y));
  }

bool intersectaConMiAngulo(Posicion &otroJugador){
  int xFinal = this.posicionX + 1;
  int yFinal = this.posicionX * tan(this->anguloDeVista);
  float pendienteRecta = (yFinal - this->posicionY) / (xFinal - this->posicionX);
  int yOtroJugador = pendiente * otroJugador.posicionX + this->posicionY;
  return (abs(yOtroJugador - otroJugador.posicionY) <= DELTA_DISTANCIA)
}
