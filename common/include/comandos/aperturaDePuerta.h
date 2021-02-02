#ifndef __APERTURA_DE_PUERTA__
#define __APERTURA_DE_PUERTA__

#include "comandos/comando.h"

class AperturaDePuerta: public Comando{

  public:
    AperturaDePuerta(int idJugador): Comando(idJugador){}

    void ejecutar(EstadoJuego &estadoJuego) override;

    std::vector<char> serializar() override{
      std::vector<char> informacion;
      informacion.push_back(idJugador);
      informacion.push_back(static_cast<int>(Accion::aperturaDePuerta));
      return informacion;
    }

    void deserializar(std::vector<char>& serializado){
        this->idJugador = (int)serializado[0];
    }

};


#endif
