#include "actualizaciones/actualizacionMovimiento.h"


ActualizacionMovimiento::ActualizacionMovimiento(Jugador *jugador) : jugador(jugador) {

}


ActualizacionMovimiento::~ActualizacionMovimiento() {

}

std::vector<char> ActualizacionMovimiento::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->obtenerId());
    informacion.insert(informacion.end(), aux.begin(), aux.end());

    std::vector<char> jugadorSerializado = jugador->serializar();
    aux = numberToCharArray(jugadorSerializado.size());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    informacion.insert(informacion.end(), jugadorSerializado.begin(), jugadorSerializado.end());

    return informacion;
}

void ActualizacionMovimiento::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    int jugadoresSize = charArrayToNumber(sub);
    idx += 4;
    std::vector<char> jugadorSerializado(serializado.begin() + idx,
                                         serializado.begin() + idx + jugadoresSize);
    this->jugador->deserializar(jugadorSerializado);

}