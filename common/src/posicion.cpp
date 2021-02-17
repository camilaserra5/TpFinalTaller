#include "../include/posicion.h"

#define DELTA_DISTANCIA 0.5
#define PI 3.1415926

#include <math.h>
#include <iostream>

Posicion::Posicion(int pixelesX, int pixelesY, float anguloDeVista) :
        pixelesX(pixelesX),
        pixelesY(pixelesY),
        anguloDeVista(anguloDeVista) {}

Posicion::~Posicion() {}

Posicion::Posicion() {}

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
  //  std::cerr << "x viejo: " << this->pixelesX << "x nuevo: " << pixelesX;
  //  std::cerr << "Y viejo: " << this->pixelesY << "Y nuevo: " << pixelesY;
    this->pixelesX = pixelesX;
    this->pixelesY = pixelesY;
}

int Posicion::pixelesEnX() {
    return this->pixelesX;
}

int Posicion::pixelesEnY() {
    return this->pixelesY;
}

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
}

void Posicion::rotar(float anguloRotacion) {
  //  std::cerr << "angulo viejo: " << this->anguloDeVista;
  //  std::cerr << "\n";
    float anguloFinal = this->anguloDeVista + anguloRotacion;
    if (anguloFinal < 0) {
        this->anguloDeVista = 2 * PI + anguloFinal;
    } else if (anguloFinal > 2 * PI) {
        this->anguloDeVista = anguloFinal - 2 * PI;
    } else {
        this->anguloDeVista = anguloFinal;
    }
  //  std::cerr << "angulo nuevo: " << this->anguloDeVista;
}

bool Posicion::operator==(Posicion &otraPosicion) {
    if (this->pixelesX == otraPosicion.pixelesEnX() && this->pixelesY == otraPosicion.pixelesEnY()) {
        return true;
    }
    return false;
}

void Posicion::setAngulo(float angulo) {
    this->anguloDeVista = angulo;
}

std::vector<char> Posicion::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(pixelesX);
    informacion.insert(informacion.end(), aux.begin(), aux.end());

    aux = numberToCharArray(pixelesY);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    int anguloSerializar = (anguloDeVista * 180) / PI;
    //std::cerr << "el ngulo que serializo es: " << anguloDeVista << " : " << anguloSerializar << std::endl;
    aux = numberToCharArray(anguloSerializar);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    return informacion;
}

void Posicion::deserializar(std::vector<char> &serializado) {
    //  std::cerr << " posicion deserializar emp " << std::endl;
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->pixelesX = charArrayToNumber(sub);
    //  std::cerr << " posicion deserializar pixelesX " << pixelesX << std::endl;
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->pixelesY = charArrayToNumber(sub);
//    std::cerr << " posicion deserializar pixelesY " << pixelesY << std::endl;
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    int anguloDeserializar = charArrayToNumber(sub);
    this->anguloDeVista = (anguloDeserializar * PI) / 180;
    //std::cerr << " posicion deserializar anguloDeVista " << anguloDeVista <<  " " << anguloDeserializar << std::endl;
//    std::cerr << " posicion deserializar fin " << std::endl;
}
