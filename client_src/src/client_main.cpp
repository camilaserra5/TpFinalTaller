#include <iostream>
#include <string>
#include "../include/cliente.h"
#include "../common_src/include/socket.h"

#define OK_CODE 0
#define ERR_CODE 1
#define NBR_PARAMS 3
#define HOST_PARAM 1
#define PORT_PARAM 2
#define USAGE "Uso: ./client <pip/hostname> <port/service>"

int main(int argc, char *argv[]) {
    if (argc != NBR_PARAMS) {
        std::cout << USAGE;
        return ERR_CODE;
    }

    char *host = argv[HOST_PARAM];
    char *port = argv[PORT_PARAM];
    try {
      std::queue cola;
        Socket socket(host, port);
        Cliente cliente(cola);
        client.run();
    } catch (...) {
        std::cout << "connect error";
        return ERR_CODE;
    }
    return OK_CODE;
}
