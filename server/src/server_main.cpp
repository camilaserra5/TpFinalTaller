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

    std::string nombreJugador = "juan";
    std::string nombre = "pepe";
    std::string nombre_partida = "grecia";
    std::string nombre_archivo = "archivo.yaml";

    ManejadorPartidas manejadorPartidas;
    bool estado = manejadorPartidas.crearPartida(nombreJugador, 1,nombre_partida, nombre_archivo);
    if (estado){
        std::cout<< "\nreo partida";
    }

    bool estado2 = manejadorPartidas.agregarClienteAPartida(nombre, nombre_partida);
    if (estado2){
        std::cout <<"\nagreggo cliente a partida";
    }

  //  cliente.start();
    std::chrono::milliseconds duration(10);
    std::this_thread::sleep_for(duration);
    //servidor.start();
  //  cliente.join();
    //servidor.join();
    return OK_CODE;
}
