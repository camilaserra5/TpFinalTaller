#include "../include/manejadorPartidas.h"

#include "map.h"
#include "protected_queue.h"
#include "comandos/comando.h"
#include "map_translator.h"
#include <yaml-cpp/yaml.h>

ManejadorPartidas::ManejadorPartidas() :
        partidas(),
        esta_corriendo(true),
        mapas() {
    this->agregarMapa("mapa1","../../resources/mapas/mapa1.yaml");
    this->agregarMapa("mapa2","../../resources/mapas/mapa2.yaml");
}

void ManejadorPartidas::agregarMapa(std::string nombreMapa, std::string archivoMapa) {
    this->mapas.insert(std::make_pair(nombreMapa, archivoMapa));
}

Map ManejadorPartidas::buscarMapa(std::string &archivoMapa) {
  std::string ruta = this->mapas.at(archivoMapa);
  return MapTranslator::yamlToMap(YAML::LoadFile(ruta));
}

int ManejadorPartidas::crearPartida(std::string &nombreJugador,
                                     int &cant_jugadores, std::string &nombre_partida,
                                     std::string &archivoMapa, Protocolo* protocolo) {
    int idCliente = -1;
    if (partidas.count(nombre_partida) > 0) {
        return idCliente;
    } else {
        Servidor *servidor = new Servidor(this->buscarMapa(archivoMapa), cant_jugadores);
        ManejadorCliente* cliente = new ManejadorCliente(servidor->obtenerColaActualizaciones(),servidor->obtenerColaEventos(),protocolo, idCliente);//cheq
        servidor->agregarCliente(nombreJugador, cliente, idCliente);
        this->partidas.insert({nombre_partida, servidor});
        return idCliente;
    }
}

int ManejadorPartidas::agregarClienteAPartida(std::string &nombreJugador,
                                               std::string &nombre_partida, Protocolo* protocolo) {

    Servidor *servidor = this->partidas.at(nombre_partida);
    int idJugador = -1;
    if (servidor->yaArranco()) {
        std::cout << "ya arranco la partida\n";
        return idJugador;
    } else {
        ManejadorCliente* cliente = new ManejadorCliente(servidor->obtenerColaActualizaciones(),servidor->obtenerColaEventos(),protocolo, idJugador);
        servidor->agregarCliente(nombreJugador, cliente, idJugador);
        return idJugador;
    }
}

void ManejadorPartidas::eliminarPartidasTerminadas() {
    std::map<std::string, Servidor *>::iterator it;
    for (it = this->partidas.begin(); it != this->partidas.end();) {
        if (it->second->terminoPartida()) {
            it->second->joinClientes();
            it->second->join();
            delete it->second;
            it = this->partidas.erase(it);
        } else {
            ++it;
        }
    }
}

void ManejadorPartidas::run() {
    while (this->esta_corriendo) {
        this->eliminarPartidasTerminadas();
        std::chrono::milliseconds duration(100);
        std::this_thread::sleep_for(duration);
        this->esta_corriendo = this->partidas.size() != 0;
    }
    /* if (this->esta_corriendo) {
         this->eliminarPartidasTerminadas();
     }*/
}

ManejadorPartidas::~ManejadorPartidas() {

}

std::vector<char> ManejadorPartidas::serializar() {
    std::vector<char> informacion;
    std::vector<char> informacionPartidas;
    std::map<std::string, Servidor *>::iterator it;
    int i = 0;
    for (it = this->partidas.begin(); it != this->partidas.end(); ++it) {
        std::pair<std::string, Servidor *> pair = *it;
        if (!pair.second->terminoPartida() && !pair.second->yaArranco()) {
            i++;
            std::vector<char> sizeNombre = numberToCharArray(pair.first.size());
            informacionPartidas.insert(informacionPartidas.end(), sizeNombre.begin(), sizeNombre.end());
            informacionPartidas.insert(informacionPartidas.end(), pair.first.begin(), pair.first.end());
            std::vector<char> partidaSerializada = pair.second->serializar();
            informacionPartidas.insert(informacionPartidas.end(), partidaSerializada.begin(), partidaSerializada.end());
        }
    }
    std::vector<char> sizePartidas = numberToCharArray(i);
    informacion.insert(informacion.end(), sizePartidas.begin(), sizePartidas.end());
    if (i > 0) {
        informacion.insert(informacion.end(), informacionPartidas.begin(), informacionPartidas.end());
    }
    return informacion;
}
