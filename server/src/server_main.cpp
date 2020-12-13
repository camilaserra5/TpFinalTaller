#include <iostream>
#include <string>
#include "socket.h"
#include "../include/cliente.h"
#include "../include/servidor.h"
#include "yaml-cpp/yaml.h"

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
<<<<<<< HEAD
    std::string nombre = "pepe";
    ProtectedQueue cola;
    Map mapa(20, 20);
    Cliente cliente(cola, nombre);
    Servidor servidor(cola, mapa, 5);
=======
    ProtectedQueue<Comando*> cola;
    Map mapa(20, 20);
    std::string nombreJugador = "juan";
    Cliente cliente(cola,nombreJugador);
    int cantidadJugadores = 1;
    Servidor servidor(cola, mapa,cantidadJugadores);
>>>>>>> 7632d0ff7eb3384ad4fd780f34707e0a0d05d0fe
    cliente.start();
    std::chrono::milliseconds duration(10);
    std::this_thread::sleep_for(duration);
    servidor.start();
    cliente.join();
    servidor.join();
    return OK_CODE;
}
