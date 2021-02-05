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

    std::vector<char> serializar() override; /* {
        std::vector<char> informacion;
        std::vector<char> aux(4);
        aux = numberToCharArray(pixelesX);
        informacion.insert(informacion.end(), aux.begin(), aux.end());

        aux = numberToCharArray(pixelesY);
        informacion.insert(informacion.end(), aux.begin(), aux.end());

        aux = numberToCharArray(anguloDeVista);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        return informacion;
    }*/

    void deserializar(std::vector<char> &serializado) override; /* {
        std::vector<char> sub(4);
        int idx = 0;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->pixelesX = charArrayToNumber(sub);

        idx += 4;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->pixelesY = charArrayToNumber(sub);

        idx += 4;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->anguloDeVista = charArrayToNumber(sub);
    }*/

private:
    int pixelesX;
    int pixelesY;
    float anguloDeVista;
};

#endif
