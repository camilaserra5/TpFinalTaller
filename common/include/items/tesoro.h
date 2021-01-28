#ifndef TESORO_H
#define TESORO_H


#include "item.h"

class Tesoro : public Item {
public:
    Tesoro(std::string &tipoDeTesoro, int &puntos, Posicion &posicion);

    ~Tesoro();

    void obtenerBeneficio(ContenedorDeElementos &contenedor, Jugador *jugador) override;



private:
    std::string &tipoDeTesoro; //va a servir para dibujar calculo;
    int puntos;
};

#endif
