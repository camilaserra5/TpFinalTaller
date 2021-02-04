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
                std::string rutaYaml,std::string nombreCliente) : Comando(idJugador),
                cantidadJugadores(cantidadJugadores),nombrePartida(nombrePartida),rutaYaml(rutaYaml),
                nombreCliente(nombreCliente) {}

    ~CrearPartida() {}

    CrearPartida(){}

    std::vector<char> serializar();

    void deserializar(std::vector<char>& serializado);

    void ejecutar(EstadoJuego &estadoJuego){}

    std::string& getNombreJugador();

    std::string& getNombrePartida();

    int& getCantJugadores();

    std::string& getRutaArchivo();

};

#endif
