#include "../include/manejadorPartidas.h"

#include "map.h"
#include "protected_queue.h"
#include "comando.h"
#include "map_translator.h"
#include <yaml-cpp/yaml.h>

ManejadorPartidas::ManejadorPartidas():
    partidas(),
    esta_corriendo(true),
    mapas(){}

/*
Map ManejadorPartidas::buscarMapa(std::string& archivoMapa){
    int i = 0;
    int cant_mapas = this->mapas.size();
    bool encontre = false;
    Map mapa(1, 1);
    while (i<cant_mapas && !encontre){
        int pos = this->mapas[i].find(archivoMapa);
        if (pos > -1){
            mapa = MapTranslator::yamlToMap(YAML::LoadFile(archivoMapa));
            encontre = true;
        }
    }
    return mapa;

}
*/
bool ManejadorPartidas::crearPartida(std::string& nombreJugador,
                  int cant_jugadores, std::string& nombre_partida,
                  std::string& archivoMapa){
    if (partidas.count(nombre_partida) > 0){
          //partida existe;
          // se avisa al cliente
          return false;
    } else {
        // partida valida
        // se le avisa al cliente que es valida
        // hay que relacionar el nombre del mapa con el archivo yaml
        // capaz esta clase tiene el un vector de yamls
      //  Map mapa = this->buscarMapa(archivoMapa);
        Map mapa(20, 20);
        Servidor* servidor = new Servidor(/*cola, actualizaciones,*/ mapa, cant_jugadores);
        Cliente* cliente = new Cliente(servidor->obtenerColaEventos(),servidor->obtenerColaActualizaciones(), nombreJugador);
        servidor->agregarCliente(nombreJugador, cliente);
        this->partidas.insert({nombre_partida, servidor});
        return true;
    }
}

bool ManejadorPartidas::agregarClienteAPartida(std::string& nombreJugador,
                                              std::string& nombre_partida){

    Servidor* servidor = this->partidas.at(nombre_partida);
    if (servidor->yaArranco()){
        // la partida ya arranco
        // informale al Cliente
        std::cout << "ya arranco la partida";
        return false;
    } else {
        // partida valida para unirse
        // avisarle al cliente;
        //ProtectedQueue<Comando*> cola;
        //ProtectedQueue<Actualizacion> actualizaciones;
        Cliente* cliente = new Cliente(servidor->obtenerColaEventos(), servidor->obtenerColaActualizaciones(), nombreJugador);
        servidor->agregarCliente(nombreJugador, cliente);
        this->partidas.insert({nombre_partida, servidor}); // no se si es necesario esto ya que no se si es la misma instancia
                                                              // que esta adentro del mapa de partidas.
                                                              // en caso de que este creo que se pisa entonces no afecta
        return true;
    }
}
void ManejadorPartidas::eliminarPartidasTerminadas(){
    std::map<std::string, Servidor*>::iterator it;
    for (it = this->partidas.begin(); it != this->partidas.end(); ++it) {
          if (it->second->terminoPartida()){
                it->second->join();
                delete it->second;
                it = this->partidas.erase(it);
                it--;
          }
    }
}

void ManejadorPartidas::run(){
    if (this->esta_corriendo){
          this->eliminarPartidasTerminadas();
    }
}

ManejadorPartidas::~ManejadorPartidas(){
  std::map<std::string, Servidor*>::iterator it;
  for (it = this->partidas.begin(); it != this->partidas.end(); ++it){
    delete it->second;
  }
}
