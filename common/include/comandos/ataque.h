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

    std::vector<char> serializar() {
        std::vector<char> info;
        return info;
    }

    void deserializar(std::vector<char> serializado) {}

    void ejecutar(EstadoJuego &estadoJuego) override;
};

#endif
