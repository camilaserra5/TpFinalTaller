#ifndef MANEJADOR_PARTIDAS_H
#define MANEJADOR_PARTIDAS_H

#include "thread.h"
#include "servidor.h"
#include "cliente.h"
#include <atomic>
#include <string>

class ManejadorPartidas : public Thread{
    public:
          ManejadorPartidas();
          ~ManejadorPartidas();
          bool crearPartida(std::string& nombreJugador,
                            int cant_jugadores, std::string& nombre_partida,
                            std::string& nombre_mapa);
          bool agregarClienteAPartida(std::string& nombreJugador,
                                      std::string& nombre_partida);
          void run();
          void eliminarPartidasTerminadas();
    private:
          std::map<std::string, Servidor*> partidas;
          std::atomic<bool> esta_corriendo;

};

#endif
