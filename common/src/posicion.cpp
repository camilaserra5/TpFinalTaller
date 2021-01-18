#include "../include/posicion.h"

#define DELTA_DISTANCIA 0.5

#include <math.h>
#include <iostream>

int Posicion::distanciaA(Posicion &posicion) {
    float x = this->pixelesX - posicion.pixelesX;
    float y = this->pixelesY - posicion.pixelesY;
    return sqrt((x * x) + (y * y));
}

bool Posicion::intersectaConMiAngulo(Posicion &otroJugador) {
    int xFinal = this->pixelesX + 1;
    int yFinal = this->pixelesX * tan(this->anguloDeVista);
    float pendienteRecta = (yFinal - this->pixelesY) / (xFinal - this->pixelesX);
    int yOtroJugador = pendienteRecta * otroJugador.pixelesX + this->pixelesY;
    return (abs(yOtroJugador - otroJugador.pixelesY) <= DELTA_DISTANCIA);
}

void Posicion::actualizar_posicion(int pixelesX, int pixelesY) {
    this->pixelesX += pixelesX;
    this->pixelesY += pixelesY;
    std::cout << "pixeles en x: " << this->pixelesX;
    std::cout << " pixeles en y " << this->pixelesY;
}

int Posicion::pixelesEnX() {
    return this->pixelesX;
}

int Posicion::pixelesEnY() {
    return this->pixelesY;
}

<<<<<<< HEAD
int Posicion::distanciaA(Posicion &posicion) {
    float x = this->pixelesX - posicion.pixelesX;
    float y = this->pixelesY - posicion.pixelesY;
    return sqrt((x * x) + (y * y));
}

bool Posicion::intersectaConMiAngulo(Posicion &otroJugador) {
    int xFinal = this->pixelesX + 1;
    int yFinal = this->pixelesX * tan(this->anguloDeVista);
    float pendienteRecta = (yFinal - this->pixelesY) / (xFinal - this->pixelesX);
    int yOtroJugador = pendienteRecta * otroJugador.pixelesX + this->pixelesY;
    return (abs(yOtroJugador - otroJugador.pixelesY) <= DELTA_DISTANCIA);
=======
// le creo un "cuerpo"(circulo) al objeto y veo si el otro objeto esta dentro de ese circulo;
//ecuacion (x2 -x1)² + (y2 - y1)² < radio²
bool Posicion::estaCerca(int &posx, int &posy) {
    int radio = 5;
    int posFinalx = posx - this->pixelesX;
    int posFinaly = posy - this->pixelesY;
    if (((posFinalx * posFinalx) + (posFinaly * posFinaly)) < radio * radio) {
        return true;
    }
    return false;
>>>>>>> main
}
