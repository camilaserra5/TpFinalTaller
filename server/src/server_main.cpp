#include <iostream>
#include "../include/servidor.h"
#include <string>

#define ARGUMENTOS_CORRECTOS 2
#define ERROR_ARGUMENTOS 1
#define ARG_PORT 1

static void mensaje_de_error_argumentos() {
    std::cerr << "La cantidad de argumentos ingresados son incorrectos. ";
    std::cerr << "Recuerde que es: ./<ejecutable> <archivo de configuracion>" << std::endl;

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
        Servidor servidor(parser);
        servidor.correr();
    } catch (std::exception &exc) {
        std::cout << exc.what() << std::endl;
        return 0;
    }

    return 0;
}
