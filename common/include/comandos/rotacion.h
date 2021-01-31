#ifndef ROTACION_H
#define ROTACION_H

#include "comando.h"
#include "iserializable.h"

class Rotacion : public Comando {

private:
    Accion sentidoDeRotacion;
public:

    Rotacion(int idJugador,Accion sentidoDeRotacion) :
    Comando(idJugador),
    sentidoDeRotacion(sentidoDeRotacion) {}

    std::vector<char> serializar() {
        std::vector<char> info;
        return info;
    }

    void deserializar(std::vector<char>& serializado);

    void ejecutar(EstadoJuego &EstadoJuego) override;

    ~Rotacion(){}
};

#endif
