#include "actualizaciones/actualizacionMovimiento.h"


ActualizacionMovimiento::ActualizacionMovimiento(Jugador *jugador) : jugador(jugador) {

}


ActualizacionMovimiento::~ActualizacionMovimiento() {
 //   delete this->jugador;
}

std::vector<char> ActualizacionMovimiento::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->obtenerId());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    std::cerr << "serializo jugadooor q se movio" << std::endl;
    std::vector<char> jugadorSerializado = jugador->serializar();
    std::cerr << "fin :) serializo jugadooor q se movio" << std::endl;
    informacion.insert(informacion.end(), jugadorSerializado.begin(), jugadorSerializado.end());

    return informacion;
}

void ActualizacionMovimiento::deserializar(std::vector<char> &serializado) {
    this->jugador = new Jugador();
    this->jugador->deserializar(serializado);
}
