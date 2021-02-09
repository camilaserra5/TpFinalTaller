#ifndef ATAQUE_H
#define ATAQUE_H
#define DANIO_MAX 10

#include "comandos/comando.h"
#include <iostream>

class Ataque : public Comando {
private:

public:
    Ataque(int idJugador);

    ~Ataque();

    std::vector<char> serializar() override;
    void deserializar(std::vector<char> &serializado) override;
    void ejecutar(EstadoJuego &estadoJuego) override;
};

#endif
