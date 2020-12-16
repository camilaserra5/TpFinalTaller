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
    int cant_jugadores = 1;

    ManejadorPartidas manejadorPartidas;
    manejadorPartidas.agregarMapa(nombre_archivo);

    bool estado = manejadorPartidas.crearPartida(nombreJugador, cant_jugadores,nombre_partida, nombre_archivo);
    if (estado){
        std::cout<< "creo partida\n";
    }
    std::chrono::milliseconds duration(10);
    std::this_thread::sleep_for(duration);
    bool estado2 = manejadorPartidas.agregarClienteAPartida(nombre, nombre_partida);
    if (estado2){
        std::cout <<"agreggo cliente a partida\n";
    }

    manejadorPartidas.run();
    return OK_CODE;
}
