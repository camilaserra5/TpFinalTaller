#include "../include/manejadorPartidas.h"
#include "map_translator.h"
#include "../include/InvalidMapException.h"
#include <config.h>
#include "../include/partida.h"
#include "comandos/crearPartida.h"
#include "comandos/unirseAPartida.h"

ManejadorPartidas::ManejadorPartidas(std::string rutaMapas, std::map<std::string, std::string> &mapas,
                                     ConfiguracionPartida configuracion) :
        partidas(),
        esta_corriendo(true),
        mapas(mapas),
        rutaMapas(std::move(rutaMapas)),
        configuracion(configuracion) {}

void ManejadorPartidas::nuevoCliente(ThClient *cliente) {
    std::vector<char> info = this->serializar();
    Comando *comando = cliente->obtenerComandoInicial(info);
    if (comando == nullptr) {
        return;
    }

    if (auto crear = dynamic_cast<CrearPartida *>(comando)) {
        this->crearPartida(crear->getNombreJugador(), crear->getCantJugadores(),
                           crear->getNombrePartida(), crear->getRutaArchivo(), crear->getScreenWidth());
        this->agregarClienteAPartida(crear->getNombreJugador(), crear->getNombrePartida(), cliente);
    }
    if (auto unirse = dynamic_cast<UnirseAPartida *>(comando)) {
        this->agregarClienteAPartida(unirse->getNombreJugador(), unirse->getNombrePartida(), cliente);
    }

    cliente->enviarIdJugador();
}

void ManejadorPartidas::cerrarPartidas() {
    this->eliminarPartidasTerminadas();
}

void ManejadorPartidas::agregarMapa(std::string nombreMapa, std::string archivoMapa) {
    this->mapas.insert(std::make_pair(nombreMapa, archivoMapa));
}

Map ManejadorPartidas::buscarMapa(std::string archivoMapa, int &anchoPantalla) {
    if (this->mapas.count(archivoMapa) == 0) {
        std::cerr << "No existe el mapa" << std::endl;
        throw InvalidMapException("mapa no cargado");
    }
    std::string ruta = this->mapas.at(archivoMapa);
    try {
        std::string pathMapas = this->rutaMapas;
        if (pathMapas.empty())
            pathMapas = MAPS_DIR;

        return MapTranslator::yamlToMap(YAML::LoadFile(pathMapas + ruta), anchoPantalla);
    } catch (YAML::BadFile &badFile) {
        std::cerr << "Error buscando mapa" << std::endl;
        throw InvalidMapException("error abriendo mapa");
    }
}

void ManejadorPartidas::crearPartida(std::string &nombreJugador, int &cant_jugadores,
                                     std::string &nombre_partida, std::string &archivoMapa,
                                     int &screenWidth) {
    if (partidas.count(nombre_partida) > 0) {
        if (partidas.at(nombre_partida)->terminoPartida() || partidas.at(nombre_partida)->yaArranco()) {
            std::cerr << "Ya existe la partida con nombre: " << nombre_partida << std::endl;
            return;
        }
    }
    try {
        Partida *servidor = new Partida(this->buscarMapa(archivoMapa, screenWidth), cant_jugadores,
                                        this->configuracion);
        std::cerr << "holi3";
        this->partidas.insert({nombre_partida, servidor});
    } catch (InvalidMapException &e) {
        std::cerr << "Error creando partida";
    }
}

void ManejadorPartidas::agregarClienteAPartida(std::string &nombreJugador,
                                               std::string &nombre_partida,
                                               ThClient *cliente) {
    Partida *partida = this->partidas.at(nombre_partida);
    if (partida->yaArranco()) {
        std::cerr << "Ya arranco la partida" << std::endl;
        return;
    }
    std::cerr << "agrego cola a clii";
    cliente->agregarColaEventos(partida->obtenerColaEventos());
    partida->agregarCliente(nombreJugador, cliente);
}

void ManejadorPartidas::eliminarPartidasTerminadas() {
    std::cerr << "entro a elimianr partidas\n";
    std::map<std::string, Partida *>::iterator it;
    std::cerr << "cantidad de partidas: " << this->partidas.size() << std::endl;
    it = this->partidas.begin();
    while (it != this->partidas.end()) {
        std::cerr << "verifico una partida\n";
        if (it->second->terminoPartida()) {
            std::cerr << "elimino partida: " << it->first << std::endl;
            it = this->partidas.erase(it);
        } else {
            ++it;
        }
    }
    std::cerr << "salgo de eliminarPartidas\n";
}

ManejadorPartidas::~ManejadorPartidas() {

}

std::vector<char> ManejadorPartidas::serializar() {
    std::vector<char> informacion;
    std::vector<char> informacionPartidas;
    std::map<std::string, Partida *>::iterator it;
    int i = 0;
    for (it = this->partidas.begin(); it != this->partidas.end(); ++it) {
        std::pair<std::string, Partida *> pair = *it;
        if (!pair.second->terminoPartida() && !pair.second->yaArranco()) {
            i++;
            std::vector<char> sizeNombre = numberToCharArray(pair.first.size());
            informacionPartidas.insert(informacionPartidas.end(), sizeNombre.begin(), sizeNombre.end());
            informacionPartidas.insert(informacionPartidas.end(), pair.first.begin(), pair.first.end());
            std::vector<char> partidaSerializada = pair.second->serializar();
            informacionPartidas.insert(informacionPartidas.end(), partidaSerializada.begin(),
                                       partidaSerializada.end());
        }
    }
    std::vector<char> sizePartidas = numberToCharArray(i);
    informacion.insert(informacion.end(), sizePartidas.begin(), sizePartidas.end());
    if (i > 0) {
        informacion.insert(informacion.end(), informacionPartidas.begin(), informacionPartidas.end());
    }
    return informacion;
}
