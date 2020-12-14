#ifndef MOVIMENTO_H
#define MOVIMIENTO_H

#include "comando.h"
#include "iserializable.h"

class ItemTomado
        : public Comando, public ISerializable {
private:
    int item = 1;
    int idJugador;
public:
    ItemTomado(int idJugador) : idJugador(idJugador) {}

    void serializar() override {}

    void deserializar() override {}

    void ejecutar(EstadoJuego &estadoJuego) override;
};

#endif
