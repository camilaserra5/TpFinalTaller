#include "actualizaciones/actualizacionMovimiento.h"


ActualizacionMovimiento::ActualizacionMovimiento(Jugador *jugador) : jugador(jugador) {

}


ActualizacionMovimiento::~ActualizacionMovimiento() {
<<<<<<< HEAD
    std::cerr << "entro al destructor de actalizacion movimiento\n";
    delete this->jugador;
=======
 //   delete this->jugador;
>>>>>>> 190dd80e3c82174bfc20e18742ff227d0c201967
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
