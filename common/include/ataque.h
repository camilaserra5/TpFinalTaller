#ifndef ATAQUE_H
#define ATAQUE_H

#include "comando.h"
#include "iserializable.h"

class Ataque : public Comando, public ISerializable {
private:
    int ataque_asociado;
    int destinox;
    int destinoy;
    int danio;
    int idJugador;
public:
    Ataque(int idJugador) : idJugador(idJugador) {}

    ~Ataque() {}

    void serializar() override {}

    void deserializar() override {}

    void ejecutar(EstadoJuego &estadoJuego) override { std::cout << "ataco pium pium\n"; }
};

#endif
