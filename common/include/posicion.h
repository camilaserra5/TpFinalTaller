#ifndef POSICION_H
#define POSICION_H

#include "iserializable.h"

class Jugador;

class Posicion : public ISerializable {
public:
    Posicion(int pixelesX, int pixelesY, float anguloDeVista);

    ~Posicion();

    Posicion();

    int distanciaA(Posicion &posicion);

    bool intersectaConMiAngulo(Posicion &otroJugador);

    void actualizar_posicion(int pixelesx, int pixelesy);

    int pixelesEnX();

    int pixelesEnY();

    void setAngulo(float angulo);

    float getAnguloDeVista() { return this->anguloDeVista; }

    bool estaCerca(int &posx, int &posy);

    void rotar(float anguloRotacion);

    bool operator==(Posicion &posicion);

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override; 

private:
    int pixelesX;
    int pixelesY;
    float anguloDeVista;
};

#endif
