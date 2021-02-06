#ifndef CAMBIO_DE_ARMA
#define CAMBIO_DE_ARMA

#include "comandos/comando.h"

class CambioDeArma : public Comando {

public:
    CambioDeArma(int idJugador) : Comando(idJugador) {}

    ~CambioDeArma() {}

    void ejecutar(EstadoJuego &estadoJuego) override;

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

};

#endif
