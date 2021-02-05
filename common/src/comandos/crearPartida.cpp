#include "comandos/crearPartida.h"

CrearPartida::CrearPartida(int idJugador, int cantidadJugadores,
                            std::string nombrePartida, std::string rutaYaml,
                            std::string nombreCliente) :
                            Comando(idJugador),
                            cantidadJugadores(cantidadJugadores),
                            nombrePartida(nombrePartida),
                            rutaYaml(rutaYaml),
                            nombreCliente(nombreCliente) {}

CrearPartida::~CrearPartida(){}

CrearPartida::CrearPartida(){}                           

std::vector<char> CrearPartida::serializar() {
    std::vector<char> info;
    std::vector<char> aux(4);
    aux = numberToCharArray(static_cast<int>(Accion::crearPartida));
    info.insert(info.end(), aux.begin(), aux.end());
    aux = numberToCharArray(this->cantidadJugadores);
    info.insert(info.end(), aux.begin(), aux.end());
    aux = numberToCharArray(this->nombrePartida.size());
    info.insert(info.end(), aux.begin(), aux.end());
    info.insert(info.end(), this->nombrePartida.begin(), this->nombrePartida.end());
    aux = numberToCharArray(this->rutaYaml.size());
    info.insert(info.end(), aux.begin(), aux.end());
    info.insert(info.end(), this->rutaYaml.begin(), this->rutaYaml.end());
    aux = numberToCharArray(this->nombreCliente.size());
    info.insert(info.end(), aux.begin(), aux.end());
    info.insert(info.end(), this->nombreCliente.begin(), this->nombreCliente.end());
    return info;
}

void CrearPartida::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->cantidadJugadores = charArrayToNumber(sub);

    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    int tamNombrePartida = charArrayToNumber(sub);

    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + tamNombrePartida]);
    this->nombrePartida = std::string(sub.begin(), sub.end());

    idx += tamNombrePartida;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    int tamRutaYaml = charArrayToNumber(sub);

    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + tamRutaYaml]);
    this->rutaYaml = std::string(sub.begin(), sub.end());

    idx += tamRutaYaml;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    int tamNombreCliente = charArrayToNumber(sub);

    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + tamNombreCliente]);
    this->nombreCliente = std::string(sub.begin(), sub.end());
}

std::string &CrearPartida::getNombreJugador() {
    return this->nombreCliente;
}

std::string &CrearPartida::getNombrePartida() {
    return this->nombrePartida;
}

int &CrearPartida::getCantJugadores() {
    return this->cantidadJugadores;
}

std::string &CrearPartida::getRutaArchivo() {
    return this->rutaYaml;
}
