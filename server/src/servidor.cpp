#include "../include/servidor.h"
#include "../include/aceptador.h"

#define TERMINAR 'q'

Servidor::Servidor(Parser &parser) : parser(parser) {}

void Servidor::correr() {
    std::string port = parser.obtenerPuerto();
    this->socket.bind_and_listen(port.c_str());
    Aceptador aceptador(this->socket, parser.obtenerRutaMapas(), parser.obtenerMapas());
    aceptador.start();

    char caracter;
    do {
        std::cin >> caracter;
    } while (caracter != TERMINAR);

    this->socket.cerrar();
    aceptador.join();
}

Servidor::~Servidor() {}
