#ifndef __APERTURA_DE_PUERTA__
#define __APERTURA_DE_PUERTA__

#include "comandos/comando.h"

class AperturaDePuerta : public Comando {

public:
    AperturaDePuerta(int idJugador);

    ~AperturaDePuerta();

    std::vector<Actualizacion *> ejecutar(EstadoJuego &estadoJuego) override;

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

};


#endif
