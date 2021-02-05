#ifndef CREAR_PARTIDA_H
#define CREAR_PARTIDA_H

#include "comando.h"

class CrearPartida: public Comando{

private:
  int cantidadJugadores;
  std::string nombrePartida;
  std::string rutaYaml;
  std::string nombreCliente;

public:
    CrearPartida(int idJugador, int cantidadJugadores,std::string nombrePartida,
                std::string rutaYaml,std::string nombreCliente);

    ~CrearPartida();

    CrearPartida();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char>& serializado) override;

    void ejecutar(EstadoJuego &estadoJuego)override{}

    std::string& getNombreJugador();

    std::string& getNombrePartida();

    int& getCantJugadores();

    std::string& getRutaArchivo();

};

#endif
