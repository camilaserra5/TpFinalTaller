#ifndef POSICION_H
#define POSICION_H

class Jugador;

class Posicion {
public:
    Posicion(int pixelesX, int pixelesY, float anguloDeVista) :
            pixelesX(pixelesX),
            pixelesY(pixelesY),
            anguloDeVista(anguloDeVista) {}

    ~Posicion() {}

    int distanciaA(Posicion &posicion);

    bool intersectaConMiAngulo(Posicion &otroJugador);

private:
    int pixelesX;
    int pixelesY;
    float anguloDeVista;
};

#endif
