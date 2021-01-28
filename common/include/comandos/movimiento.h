#ifndef MOVIMENTO_H
#define MOVIMIENTO_H

#include "comando.h"
#include "estadoJuego.h"
#include <iostream>

class Movimiento : public Comando{
private:
    Accion tipo_de_movimiento;
    int idJugador;
public:
    Movimiento(int &idJugador, Accion tipo_de_movimiento);

    void ejecutar(EstadoJuego &EstadoJuego) override;

    ~Movimiento();

    std::vector<char> serializar() {
        std::vector<char> info;
        return info;
    }

    void deserializar(std::vector<char> serializado) {}
};

#endif
