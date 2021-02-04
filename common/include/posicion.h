#ifndef POSICION_H
#define POSICION_H

#include "iserializable.h"
class Jugador;

class Posicion : public ISerializable {
public:
    Posicion(int pixelesX, int pixelesY, float anguloDeVista) :
            pixelesX(pixelesX),
            pixelesY(pixelesY),
            anguloDeVista(anguloDeVista) {}

    ~Posicion() {}
    Posicion(){}
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

    std::vector<char> serializar() override {
        std::vector<char> informacion;
        informacion.push_back(pixelesX);
        informacion.push_back(pixelesY);
        informacion.push_back(anguloDeVista);
        return informacion;
    }

    void deserializar(std::vector<char>& serializado) override {
        this->pixelesX = serializado[0];
        this->pixelesY = serializado[1];
        this->anguloDeVista = serializado[2];
    }

private:
    int pixelesX;
    int pixelesY;
    float anguloDeVista;
};

#endif
