#ifndef __DESCONECTAR_JUGADOR__
#define __DESCONECTAR_JUGADOR__

#include "comandos/comando.h"

class DesconectarJugador : public Comando {

public:
    DesconectarJugador(int idJugador);

    ~DesconectarJugador();

    std::vector<Actualizacion *> ejecutar(EstadoJuego &estadoJuego) override;

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

};


#endif
