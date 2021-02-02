#ifndef ATAQUE_H
#define ATAQUE_H
#define DANIO_MAX 10

#include "comandos/comando.h"
#include <iostream>

class Ataque : public Comando {
private:
    //  int destinox;
    //int destinoy;
public:
    Ataque(int idJugador) : Comando(idJugador) {}

    ~Ataque() {}

    std::vector<char> serializar() {
        std::vector<char> info;
        info.push_back(idJugador);
        info.push_back(static_cast<int>(Accion::ataque));
        return info;
    }

    void deserializar(std::vector<char>& serializado) {
        this->idJugador= (int)serializado[0];
    }

    void ejecutar(EstadoJuego &estadoJuego) override;
};

#endif
