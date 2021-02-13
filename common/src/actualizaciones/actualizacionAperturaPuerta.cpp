#include "actualizaciones/actualizacionAperturaPuerta.h"


ActualizacionAperturaPuerta::ActualizacionAperturaPuerta(Puerta &puerta) : puerta(puerta) {}


ActualizacionAperturaPuerta::~ActualizacionAperturaPuerta() {}

std::vector<char> ActualizacionAperturaPuerta::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->obtenerId());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    std::vector<char> puertaSerializada = this->puerta.serializar();
    informacion.insert(informacion.end(), puertaSerializada.begin(), puertaSerializada.end());
    return informacion;
}

void ActualizacionAperturaPuerta::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    std::vector<char> puertaSerializada(serializado.begin(),
                                        serializado.end());
    this->puerta.deserializar(puertaSerializada);
}
