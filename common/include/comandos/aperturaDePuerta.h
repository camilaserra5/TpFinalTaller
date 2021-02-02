#ifndef __APERTURA_DE_PUERTA__
#define __APERTURA_DE_PUERTA__

#include "comandos/comando.h"

class AperturaDePuerta: public Comando{

  public:
    AperturaDePuerta(int idJugador): Comando(idJugador){}

    void ejecutar(EstadoJuego &estadoJuego) override;

    std::vector<char> serializar() override{
      std::vector<char> s;
      return s;
    }

    void deserializar(std::vector<char>& serializado){}

};


#endif
