#include "actualizaciones/actualizacionCambioArma.h"


ActualizacionCambioArma::ActualizacionCambioArma(int &id, int &idArmaActual) :
        id(id), armaActual(idArmaActual) {}


ActualizacionCambioArma::~ActualizacionCambioArma() {}

std::vector<char> ActualizacionCambioArma::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->obtenerId());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(this->id);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(this->armaActual);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    return informacion;
}

void ActualizacionCambioArma::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->id = charArrayToNumber(sub);
    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->armaActual = charArrayToNumber(sub);
}
