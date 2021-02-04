#ifndef MOVIMENTO_H
#define MOVIMIENTO_H

#include "comando.h"
#include "estadoJuego.h"
#include <iostream>

class Movimiento : public Comando {
private:
    Accion tipo_de_movimiento;
public:
    Movimiento(int &idJugador, Accion tipo_de_movimiento);

    void ejecutar(EstadoJuego &EstadoJuego) override;

    ~Movimiento();

    std::vector<char> serializar() {
        std::vector<char> info;
        info.push_back(idJugador);
        info.push_back(static_cast<int>(this->tipo_de_movimiento));
        return info;
    }

    void deserializar(std::vector<char>& serializado) {
        this->idJugador = (int)serializado[0];
        this->tipo_de_movimiento = static_cast<Accion>(serializado[1]);
    }
};

#endif
