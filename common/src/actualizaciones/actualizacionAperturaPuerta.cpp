#include "actualizaciones/actualizacionAperturaPuerta.h"


ActualizacionAperturaPuerta::ActualizacionAperturaPuerta(Puerta& puerta): puerta(puerta){}


ActualizacionAperturaPuerta::~ActualizacionAperturaPuerta() {}

std::vector<char> ActualizacionAperturaPuerta::serializar() {
    std::vector<char> informacion;
    return informacion;
}

void ActualizacionAperturaPuerta::deserializar(std::vector<char> &serializado) {

}
