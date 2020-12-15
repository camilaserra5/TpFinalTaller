#ifndef ATAQUE_H
#define ATAQUE_H
#define DANIO_MAX 10

#include "comandos/comando.h"
#include "iserializable.h"

class Ataque : public Comando, public ISerializable {
private:
    int destinox;
    int destinoy;
    int danio;
    int idJugador;
public:
    Ataque(int idJugador) : idJugador(idJugador) {}

    ~Ataque() {}

    void serializar() override {}

    void deserializar() override {}

    void ejecutar(EstadoJuego &estadoJuego) override;
};

#endif
