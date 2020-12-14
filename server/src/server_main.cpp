#include <iostream>
#include <string>
#include "socket.h"
#include "../include/cliente.h"
#include "../include/servidor.h"
#include "yaml-cpp/yaml.h"
#include "../include/manejadorPartidas.h"
#define OK_CODE 0
#define ERR_CODE 1
#define USAGE "Uso: ./server <config_file>"

int main(int argc, char *argv[]) {
    //YAML::Node config = YAML::LoadFile(argv[1]);
    //  const std::string port = config["port"].as<std::string>();
/*
   Socket socket;
    if (socket.bind(argv[1]) != OK_CODE) {
        std::cout << "bind error";
        return ERR_CODE;
    }
    if (socket.listen() != OK_CODE) {
        std::cout << "listen error";
        return ERR_CODE;
    }*/

  //  ProtectedQueue<Comando*> comandos;
  //  ProtectedQueue<Actualizacion*> actualizaciones;
    //Map mapa(20, 20);
    std::string nombreJugador = "juan";
    std::string nombre = "pepe";
    std::string nombre_partida = "grecia";
    std::string nombre_archivo = "archivo.yaml";
/*    Cliente cliente(comandos,actualizaciones,nombreJugador);
    int cantidadJugadores = 1;
    Servidor servidor(comandos, actualizaciones, mapa,cantidadJugadores);
*/
    ManejadorPartidas manejadorPartidas;
    bool estado = manejadorPartidas.crearPartida(nombreJugador, 1,nombre_partida, nombre_archivo);
    if (estado){
        std::cout<< "creo partida";
    }

    bool estado2 = manejadorPartidas.agregarClienteAPartida(nombre, nombre_partida);
    if (estado2){
        std::cout <<"agreggo cliente a partida";
    }

  //  cliente.start();
    std::chrono::milliseconds duration(10);
    std::this_thread::sleep_for(duration);
    //servidor.start();
  //  cliente.join();
    //servidor.join();
    return OK_CODE;
}
