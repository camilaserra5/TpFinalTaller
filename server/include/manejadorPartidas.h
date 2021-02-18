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

class ManejadorPartidas : public ISerializable {
public:
    ManejadorPartidas(std::string &rutaMapas, std::map<std::string, std::string> &mapas);

    ~ManejadorPartidas();

    void cerrarPartidas();

    int crearPartida(std::string &nombreJugador, int &cant_jugadores,
                     std::string &nombre_partida, std::string &archivoMapa,
                     Protocolo *protocolo, int &screenWidth);

    int agregarClienteAPartida(std::string &nombreJugador,
                               std::string &nombre_partida, Protocolo *protocolo);

    std::vector<char> serializar();

    void deserializar(std::vector<char> &serializado) {}

    void run();

    void eliminarPartidasTerminadas();

    Map buscarMapa(std::string &archivoMapa, int &anchoPantalla);

    void agregarMapa(std::string nombreMapa, std::string archivoMapa);

private:
    std::map<std::string, Servidor *> partidas;
    std::atomic<bool> esta_corriendo;
    std::map<std::string, std::string> &mapas;
    std::string &rutaMapas;

};

#endif
