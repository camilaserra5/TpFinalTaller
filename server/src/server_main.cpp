#include <iostream>
#include <string>
#include "socket.h"
#include "../include/old_cliente.h"
#include "../include/servidor.h"
#include "yaml-cpp/yaml.h"
#include "../include/manejadorPartidas.h"
#include "../include/parser.h"
#include "../include/aceptador.h"


#define ARGUMENTOS_CORRECTOS 2
#define ERROR_ARGUMENTOS 1
#define ARG_PORT 1


static void mensaje_de_error_argumentos() {
    printf("La cantidad de argumentos ingresados son incorrectos. ");
    printf("Recuerde que es: ./<ejecutable> <archivo de configuracion>\n");
}

static bool verifica_argumentos(int argc, const char *argv[]) {
    if (argc != ARGUMENTOS_CORRECTOS) {
        mensaje_de_error_argumentos();
        return false;
    }
    return true;
}

int main(int argc, const char *argv[]) {
    if (!verifica_argumentos(argc, argv)) {
        return ERROR_ARGUMENTOS;
    }
    try {
        Parser parser(argv[ARG_PORT]);
        std::string port = parser.obtenerPuerto();
        std::cerr << " puerto: " << port;
        Socket socket;
        socket.bind_and_listen(port.c_str());

        std::string nombreJugador = "juan";
        std::string nombre = "pepe";
        std::string nombre_partida = "grecia";
        std::string nombre_partida2 = "ketchup";
        std::string nombre_archivo = "archivo.yaml";
        int cant_jugadores = 1;
        int cant_jugadores2 = 2;
        ManejadorPartidas manejadorPartidas;

        Aceptador aceptador(socket, &manejadorPartidas);
        aceptador.start();
        char c;
        while ((c = std::cin.get()) != 'q'){
        }
        manejadorPartidas.cerrarPartidas();
        aceptador.cerrar();
        aceptador.join();
    } catch (std::exception &exc) {
        std::cout << exc.what() << std::endl;
        return 0;
    }

    return 0;
}
