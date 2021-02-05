#include "comandos/unirseAPartida.h"

std::vector<char> UnirseAPartida::serializar() {
    std::vector<char> info;
    std::vector<char> idPartida = numberToCharArray(static_cast<int>(Accion::unirseAPartida));
    info.insert(info.end(), idPartida.begin(), idPartida.end());
    std::vector<char> nombrePartSize = numberToCharArray(this->nombrePartida.size());
    info.insert(info.end(), nombrePartSize.begin(), nombrePartSize.end());
    info.insert(info.end(), this->nombrePartida.begin(), this->nombrePartida.end());
    std::vector<char> nombreCliSize = numberToCharArray(this->nombreCliente.size());
    info.insert(info.end(), nombreCliSize.begin(), nombreCliSize.end());
    info.insert(info.end(), this->nombreCliente.begin(), this->nombreCliente.end());
    return info;
}

void UnirseAPartida::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 1;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 3]);
    int tamNombrePartida = charArrayToNumber(sub);

    idx += 3;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + tamNombrePartida]);
    this->nombrePartida = std::string(sub.begin(), sub.end());

    idx += tamNombrePartida;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 3]);
    int tamNombreCliente = charArrayToNumber(sub);

    idx += 3;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + tamNombreCliente]);
    this->nombreCliente = std::string(sub.begin(), sub.end());

    std::cout << "nom " << this->nombrePartida << "n omcli " << this->nombreCliente;
}

std::string &UnirseAPartida::getNombreJugador() {
    return this->nombreCliente;
}

std::string &UnirseAPartida::getNombrePartida() {
    return this->nombrePartida;
}
