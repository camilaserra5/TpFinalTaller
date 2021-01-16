#include "../include/manejadorPartidas.h"

#include "map.h"
#include "protected_queue.h"
#include "comandos/comando.h"
#include "map_translator.h"
#include <yaml-cpp/yaml.h>

ManejadorPartidas::ManejadorPartidas() :
        partidas(),
        esta_corriendo(true),
        mapas() {}

void ManejadorPartidas::agregarMapa(std::string &archivoMapa){
    this->mapas.push_back(archivoMapa);
}

Map ManejadorPartidas::buscarMapa(std::string &archivoMapa) {
    int i = 0;
    int cant_mapas = this->mapas.size();
    bool encontre = false;
    //Map* mapa = new Map(1, 1);
    Map mapa(20,20);
    mapa.setValue(0,1, Type::comida);
    while (i < cant_mapas && !encontre) {
        int pos = this->mapas[i].find(archivoMapa);
        if (pos > -1) {
            mapa = MapTranslator::yamlToMap(YAML::LoadFile(archivoMapa));
            encontre = true;
        }
    }
    return mapa;

}

bool ManejadorPartidas::crearPartida(std::string &nombreJugador,
                                     int& cant_jugadores, std::string &nombre_partida,
                                     std::string &archivoMapa) {
    if (partidas.count(nombre_partida) > 0) {
        //partida existe;
        // se avisa al cliente
        return false;
    } else {
        // partida valida
        // se le avisa al cliente que es valida
        // hay que relacionar el nombre del mapa con el archivo yaml
        // capaz esta clase tiene el un vector de yamls
        //Map mapa = this->buscarMapa(archivoMapa);
        Map *mapa = new Map(20, 20);
        mapa->setValue(0,1, Type::comida);
        std::cout << "ya setie elemnto";
        //int cant_jugadores = 1;
        Servidor *servidor = new Servidor(mapa, cant_jugadores);
        //  Cliente *cliente = new Cliente(servidor.obtenerColaEventos(), servidor.obtenerColaActualizaciones(),  nombreJugador);
        //servidor.agregarCliente(nombreJugador, cliente);
        this->partidas.insert({nombre_partida, servidor});
        return true;
    }
}

bool ManejadorPartidas::agregarClienteAPartida(std::string &nombreJugador,
                                               std::string &nombre_partida) {

    Servidor *servidor = this->partidas.at(nombre_partida);
    if (servidor->yaArranco()) {
        // la partida ya arranco
        // informale al Cliente
        std::cout << "ya arranco la partida\n";
        return false;
    } else {
        // partida valida para unirse
        // avisarle al cliente;
        //ProtectedQueue<Comando*> cola;
        //ProtectedQueue<Actualizacion> actualizaciones;
        std::string nombre = "juan";
        Cliente *cliente = new Cliente(servidor->obtenerColaEventos(), servidor->obtenerColaActualizaciones(), nombre);
        servidor->agregarCliente(nombre, cliente);
        //this->partidas.insert({nombre_partida, servidor}); // no se si es necesario esto ya que no se si es la misma instancia
        // que esta adentro del mapa de partidas.
        // en caso de que este creo que se pisa entonces no afecta
        return true;
    }
}

void ManejadorPartidas::eliminarPartidasTerminadas() {
    std::map<std::string, Servidor *>::iterator it;
    for (it = this->partidas.begin(); it != this->partidas.end();) {
        if (it->second->terminoPartida()) {
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
