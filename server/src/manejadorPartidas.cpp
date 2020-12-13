#include "../include/manejadorPartidas.h"

#include "map.h"
#include "protected_queue.h"
#include "comando.h"


ManejadorPartidas::ManejadorPartidas():
    partidas(),
    esta_corriendo(true){}

ManejadorPartidas::~ManejadorPartidas(){}

bool ManejadorPartidas::crearPartida(std::string& nombreJugador,
                  int cant_jugadores, std::string& nombre_partida,
                  std::string& nombre_mapa){
    if (partidas.count(nombre_partida) > 0){
          //partida existe;
          // se avisa al cliente
          return false;
    } else {
        // partida valida
        // se le avisa al cliente que es valida
        // hay que relacionar el nombre del mapa con el archivo yaml
        // capaz esta clase tiene el un vector de yamls
        Map mapa(20, 20);
        ProtectedQueue<Comando*> cola;
        Servidor* servidor = new Servidor(cola, mapa, cant_jugadores);
        Cliente* cliente = new Cliente(cola, nombreJugador);
        servidor->agregarCliente(nombreJugador, *cliente);
        this->partidas.insert({nombre_partida, servidor});
        return true;
    }
}

bool ManejadorPartidas::agregarClienteAPartida(std::string& nombreJugador,
                                              std::string& nombre_partida){

    Servidor* servidor = this->partidas.at(nombre_partida);
    if (servidor->yaArranco()){
        // la partida ya arranco
        // informale al cliente
        return false;
    } else {
        // partida valida para unirse
        // avisarle al cliente;
        ProtectedQueue<Comando*> cola;
        Cliente* cliente = new Cliente(cola, nombreJugador);
        servidor->agregarCliente(nombreJugador, *cliente);
        this->partidas.insert({nombre_partida, servidor}); // no se si es necesario esto ya que no se si es la misma instancia
                                                              // que esta adentro del mapa de partidas.
                                                              // en caso de que este creo que se pisa entonces no afecta
        return true;
    }
}
void ManejadorPartidas::eliminarPartidasTerminadas(){
    std::map<std::string, Servidor*>::iterator it;
    for (it = this->partidas.begin(); it != partidas.end(); ++it) {
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
