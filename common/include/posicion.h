#ifndef POSICION_H
#define POSICION_H

class Jugador;

class Posicion {
public:
    Posicion(int posicionX, int posicionY, float anguloDeVista) :
            posicionX(posicionX),
            posicionY(posicionY),
            anguloDeVista(anguloDeVista) {}

    ~Posicion() {}

    int distanciaA(Posicion &posicion) { return -1; }

    int intersectaConMiAngulo(Posicion &otroJugador) { return -1; }

private:
    int posicionX;
    int posicionY;
    float anguloDeVista;
};

#endif
