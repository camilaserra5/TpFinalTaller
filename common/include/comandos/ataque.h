#ifndef ATAQUE_H
#define ATAQUE_H
#define DANIO_MAX 10

#include "comandos/comando.h"
#include <iostream>

class Ataque : public Comando {
private:
  //  int destinox;
    //int destinoy;
    int idJugador;
public:
    Ataque(int idJugador) : idJugador(idJugador) {}

    ~Ataque() {}

    std::stringstream serializar() override;

    void deserializar() override {}

    void ejecutar(EstadoJuego &estadoJuego) override;
};

#endif
