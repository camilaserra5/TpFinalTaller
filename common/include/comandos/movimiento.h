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
    
    std::vector<char> serializar() override; /* {
        std::vector<char> informacion;
        std::vector<char> aux(4);
        aux = numberToCharArray(idJugador);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        aux = numberToCharArray(static_cast<int>(this->tipo_de_movimiento));
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        return informacion;
    }*/

    void deserializar(std::vector<char> &serializado) override; /* {
        std::vector<char> sub(4);
        int idx = 0;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->idJugador = charArrayToNumber(sub);

        idx += 4;
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        this->tipo_de_movimiento = static_cast<Accion>(charArrayToNumber(sub));
    }*/
};

#endif
