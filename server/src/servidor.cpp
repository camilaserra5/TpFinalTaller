#include "../include/servidor.h"
#include "../include/aceptador.h"


Servidor::Servidor(Parser &parser) : parser(parser),
                  aceptador(this->socket, parser.obtenerRutaMapas(),
                          parser.obtenerMapas()) {}

void Servidor::correr() {
    std::string port = parser.obtenerPuerto();
    this->socket.bind_and_listen(port.c_str());
    this->aceptador.start();
}

void Servidor::cerrar(){
    this->socket.cerrar();
    aceptador.join();
}

Servidor::~Servidor() {}
