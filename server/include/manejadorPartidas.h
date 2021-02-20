#ifndef MANEJADOR_PARTIDAS_H
#define MANEJADOR_PARTIDAS_H

#include "thread.h"
#include "servidor.h"
#include <atomic>
#include <string>
#include <map>
#include <vector>
#include "map.h"
#include "protocolo.h"
#include "../include/thclient.h"
#include "../include/partida.h"

class ManejadorPartidas : public ISerializable {
public:
    ManejadorPartidas(std::string rutaMapas, std::map<std::string, std::string> &mapas);

    ~ManejadorPartidas();

    void nuevoCliente(ThClient *cliente);

    void cerrarPartidas();

    void crearPartida(std::string &nombreJugador, int &cant_jugadores,
                     std::string &nombre_partida, std::string &archivoMapa,
                     int &screenWidth);

    void agregarClienteAPartida(std::string &nombreJugador,
                               std::string &nombre_partida, ThClient *cliente);

    std::vector<char> serializar();

    void deserializar(std::vector<char> &serializado) {}

    void run();

    void eliminarPartidasTerminadas();

    Map buscarMapa(std::string archivoMapa, int &anchoPantalla);

    void agregarMapa(std::string nombreMapa, std::string archivoMapa);

private:
    std::map<std::string, Partida *> partidas;
    std::atomic<bool> esta_corriendo;
    std::map<std::string, std::string> &mapas;
    std::string rutaMapas;
};

#endif
