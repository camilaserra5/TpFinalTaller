#include "lienzo.h"

Lienzo::Lienzo(int x, int y, int ancho, int alto) :
        x(x), y(y), ancho(ancho), alto(alto) {
}

int Lienzo::getX() const {
    return this->x;
}

int Lienzo::getY() const {
    return this->y;
}

int Lienzo::getAncho() const {
    return this->ancho;
}

int Lienzo::getAlto() const {
    return this->alto;
}

void Lienzo::actualizar(int una_x, int una_y, int un_alto, int un_ancho) {
    this->x = una_x;
    this->y = una_y;
    this->alto = un_alto;
    this->ancho = un_ancho;
}
