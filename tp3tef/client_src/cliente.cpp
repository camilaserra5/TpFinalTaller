#include "cliente.h"
#include <iostream>
#include <fstream>
#include <string>

#define BUFFER_TAM 50
#define ERROR -1

#define SOCKET_CERRADO 0

Cliente::Cliente(const char *host, const char *server_port) : socket() {
    this->socket.conectar(host, server_port);
}

void Cliente::correr() {

}

Cliente::~Cliente() {}
