#include <iostream>
#include "../include/cliente.h"

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
    try {
        Cliente cliente(argv[HOST_PARAM], argv[PORT_PARAM]);
        cliente.run();
        //PENSAR SI N OIES MEJOR TIRAR UN HILO QUE AGARRE LOS EVENTOS Y
        //LOS VAYA MANDANDO/RECIBIENDO ACTUALIZACIONES
    } catch (...) {
        std::cout << "connect error";
        return ERR_CODE;
    }
    return OK_CODE;
}