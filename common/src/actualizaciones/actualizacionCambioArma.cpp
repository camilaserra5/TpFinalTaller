#include "actualizaciones/actualizacionCambioArma.h"


ActualizacionCambioArma::ActualizacionCambioArma(int& id, int& idArmaActual):
        id(id), armaActual(idArmaActual){}


ActualizacionCambioArma::~ActualizacionCambioArma() {}

std::vector<char> ActualizacionCambioArma::serializar() {
    std::vector<char> informacion;
    return informacion;
}

void ActualizacionCambioArma::deserializar(std::vector<char> &serializado) {

}
