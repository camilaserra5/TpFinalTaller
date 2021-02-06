#include "comandos/unirseAPartida.h"

UnirseAPartida::UnirseAPartida(int idJugador, std::string nombrePartida,
                               std::string nombreCliente) :
        Comando(idJugador),
        nombrePartida(nombrePartida),
        nombreCliente(nombreCliente) {}

UnirseAPartida::~UnirseAPartida() {}

UnirseAPartida::UnirseAPartida() {}


std::vector<char> UnirseAPartida::serializar() {
    std::vector<char> info;
    std::vector<char> aux(4);
    aux = numberToCharArray(static_cast<int>(Accion::unirseAPartida));
    info.insert(info.end(), aux.begin(), aux.end());
    aux = numberToCharArray(this->nombrePartida.size());
    info.insert(info.end(), aux.begin(), aux.end());
    info.insert(info.end(), this->nombrePartida.begin(), this->nombrePartida.end());
    aux = numberToCharArray(this->nombreCliente.size());
    info.insert(info.end(), aux.begin(), aux.end());
    info.insert(info.end(), this->nombreCliente.begin(), this->nombreCliente.end());
    return info;
}

void UnirseAPartida::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    int tamNombrePartida = charArrayToNumber(sub);

    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + tamNombrePartida]);
    this->nombrePartida = std::string(sub.begin(), sub.end());

    idx += tamNombrePartida;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    int tamNombreCliente = charArrayToNumber(sub);

    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + tamNombreCliente]);
    this->nombreCliente = std::string(sub.begin(), sub.end());
}

std::string &UnirseAPartida::getNombreJugador() {
    return this->nombreCliente;
}

std::string &UnirseAPartida::getNombrePartida() {
    return this->nombrePartida;
}
