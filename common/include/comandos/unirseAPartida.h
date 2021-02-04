#ifndef UNIRSE_A_PARTIDA
#define UNIRSE_A_PARTIDA

#include "comando.h"

class UnirseAPartida: public Comando{

private:
  std::string nombrePartida;
  std::string nombreCliente;

public:
    UnirseAPartida(int idJugador,std::string nombrePartida,std::string nombreCliente) : Comando(idJugador),
    nombrePartida(nombrePartida),nombreCliente(nombreCliente){}

    ~UnirseAPartida() {}

    std::vector<char> serializar() override;

    void deserializar(std::vector<char>& serializado) override;

    void ejecutar(EstadoJuego &estadoJuego){}

    std::string& getNombreJugador();

    std::string& getNombrePartida();
};

#endif
