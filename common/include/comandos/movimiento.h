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

    Movimiento();

    std::vector<char> serializar() override;
    void deserializar(std::vector<char> &serializado) override;
};

#endif
