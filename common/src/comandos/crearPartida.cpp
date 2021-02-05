#include "comandos/crearPartida.h"

std::vector<char> CrearPartida::serializar() {
    std::vector<char> info;
    std::vector<char> idPartida = numberToCharArray(static_cast<int>(Accion::crearPartida));
    info.insert(info.end(), idPartida.begin(), idPartida.end());
    std::vector<char> cantJugadores = numberToCharArray(this->cantidadJugadores);
    info.insert(info.end(), cantJugadores.begin(), cantJugadores.end());
    std::vector<char> nombrePartSize = numberToCharArray(this->nombrePartida.size());
    info.insert(info.end(), nombrePartSize.begin(), nombrePartSize.end());
    info.insert(info.end(), this->nombrePartida.begin(), this->nombrePartida.end());
    std::vector<char> rutaYamlSize = numberToCharArray(this->rutaYaml.size());
    info.insert(info.end(), rutaYamlSize.begin(), rutaYamlSize.end());
    info.insert(info.end(), this->rutaYaml.begin(), this->rutaYaml.end());
    std::vector<char> nombreCliSize = numberToCharArray(this->nombreCliente.size());
    info.insert(info.end(), nombreCliSize.begin(), nombreCliSize.end());
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
