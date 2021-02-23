#include "../include/posicion.h"

#define DELTA_DISTANCIA 10
#define PI 3.1415926

#include <math.h>

Posicion::Posicion(int pixelesX, int pixelesY, float anguloDeVista) :
        pixelesX(pixelesX),
        pixelesY(pixelesY),
        anguloDeVista(anguloDeVista) {}

Posicion::~Posicion() {}

Posicion::Posicion() {}

float Posicion::distanciaA(Posicion &posicion) {
    float x = this->pixelesX - posicion.pixelesX;
    float y = this->pixelesY - posicion.pixelesY;
    return sqrt((x * x) + (y * y));
}

bool Posicion::verificarSiPerteneceAlSegmento(Posicion &otroJugador) {
    float xMin, xMax;
    if ((0 <= anguloDeVista && anguloDeVista < PI / 2) || (3 * PI / 2 <= anguloDeVista && anguloDeVista < 2 * PI)) {
        xMin = this->pixelesX;
        return (xMin <= otroJugador.pixelesX);
    } else {
        xMax = pixelesX;
        return (otroJugador.pixelesX <= xMax);
    }
}

bool Posicion::intersectaConMiAngulo(Posicion &otroJugador) {
//  std::cerr << "verifico las posiciones de los jugadores inteersecando\n";
//  std::cerr << "la pos del atacante es x: " << pixelesX << " y: " << pixelesY << "angulo: " << anguloDeVista << "\n";
//  std::cerr << "la pos del atacado es x: " << otroJugador.pixelesX << " y: " << otroJugador.pixelesY << "angulo: " << otroJugador.anguloDeVista << "\n";
    bool estaEnSegmento = verificarSiPerteneceAlSegmento(otroJugador);
    if (!estaEnSegmento) return false;
    float pendienteRecta = tan(anguloDeVista);
    /*if ((PI <= anguloDeVista && anguloDeVista < 3 * PI/2) || (3 * PI/2 <= anguloDeVista && anguloDeVista < 2 * PI)){
      pendienteRecta = -pendienteRecta;
    }*/
    float ordenadaOrigen = -pixelesY - (pendienteRecta * pixelesX);
    float y = pendienteRecta * otroJugador.pixelesX + ordenadaOrigen;
    if (y < 0) y = (-1) * y;
    //std::cerr << "el delta distancia es: " << abs (y - otroJugador.pixelesY) << std::endl;
    return (abs(y - otroJugador.pixelesY) <= DELTA_DISTANCIA);
}

void Posicion::actualizar_posicion(int pixelesX, int pixelesY) {
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
bool Posicion::estaCerca(int &posx, int &posy, float radio) {
    Posicion posicionJugador(posx, posy, 0);
    return this->distanciaA(posicionJugador) <= radio;
}

void Posicion::rotar(float anguloRotacion) {
    float anguloFinal = this->anguloDeVista + anguloRotacion;
    if (anguloFinal < 0) {
        this->anguloDeVista = 2 * PI + anguloFinal;
    } else if (anguloFinal > 2 * PI) {
        this->anguloDeVista = anguloFinal - 2 * PI;
    } else {
        this->anguloDeVista = anguloFinal;
    }
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
    aux = numberToCharArray(anguloSerializar);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    return informacion;
}

void Posicion::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->pixelesX = charArrayToNumber(sub);
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->pixelesY = charArrayToNumber(sub);
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    int anguloDeserializar = charArrayToNumber(sub);
    this->anguloDeVista = (anguloDeserializar * PI) / 180;
}
