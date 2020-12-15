#ifndef MANEJADOR_PARTIDAS_H
#define MANEJADOR_PARTIDAS_H

#include "thread.h"
#include "servidor.h"
#include "cliente.h"
#include <atomic>
#include <string>
#include <map>
#include <vector>
#include "map.h"

class ManejadorPartidas : public Thread {
public:
    ManejadorPartidas();

    ~ManejadorPartidas();

    bool crearPartida(std::string &nombreJugador,
                      int cant_jugadores, std::string &nombre_partida,
                      std::string &archivoMapa);

    bool agregarClienteAPartida(std::string &nombreJugador,
                                std::string &nombre_partida);

    void run();

    void eliminarPartidasTerminadas();

    Map buscarMapa(std::string &archivoMapa);

private:
    std::map<std::string, Servidor *> partidas;
    std::atomic<bool> esta_corriendo;
    std::vector<std::string> mapas;

};

#endif
