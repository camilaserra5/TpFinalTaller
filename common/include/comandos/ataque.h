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

    std::vector<char> serializar() override {
        std::vector<char> informacion;
        std::vector<char> aux(4);
        aux = numberToCharArray(idJugador);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        aux = numberToCharArray(static_cast<int>(Accion::ataque));
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        return informacion;
    }

    void deserializar(std::vector<char> &serializado) {
        std::vector<char> sub(4);
        int idx = 0;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->idJugador = charArrayToNumber(sub);
    }

    void ejecutar(EstadoJuego &estadoJuego) override;
};

#endif
