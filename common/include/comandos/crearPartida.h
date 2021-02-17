#ifndef CREAR_PARTIDA_H
#define CREAR_PARTIDA_H

#include "comando.h"

class CrearPartida : public Comando {

private:
    int cantidadJugadores;
    std::string nombrePartida;
    std::string rutaYaml;
    std::string nombreCliente;
    int screenWidth;

public:
    CrearPartida(int idJugador, int cantidadJugadores, std::string nombrePartida,
                 std::string rutaYaml, std::string nombreCliente, int screenWidth);

    ~CrearPartida();

    CrearPartida();

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &serializado) override;

    std::vector<Actualizacion*> ejecutar(EstadoJuego &estadoJuego) override {}

    std::string &getNombreJugador();

    std::string &getNombrePartida();

    int &getCantJugadores();

    std::string &getRutaArchivo();

    int &getScreenWidth();


};

#endif
