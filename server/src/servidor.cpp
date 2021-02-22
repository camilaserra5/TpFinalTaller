#include "../include/servidor.h"
#include "../include/aceptador.h"
#include "configuracionPartida.h"


Servidor::Servidor(Parser &parser, ConfiguracionPartida &config) : parser(parser),
                                                                   aceptador(this->socket, parser.obtenerRutaMapas(),
                                                                             parser.obtenerMapas(), config) {}

void Servidor::correr() {
    std::string port = parser.obtenerPuerto();
    this->socket.bind_and_listen(port.c_str());
    this->aceptador.start();
}

void Servidor::cerrar() {
    this->socket.cerrar();
    aceptador.join();
}

Servidor::~Servidor() {}
