#include "actualizaciones/actualizacionInicioPartida.h"

ActualizacionInicioPartida::ActualizacionInicioPartida(std::vector<char>& informacion) :
        informacion(informacion), estadoJuego(){
}

ActualizacionInicioPartida::~ActualizacionInicioPartida() {
  std::cerr << "entro al destructor de actalizacion inicializo partida\n";
}

std::vector<char> ActualizacionInicioPartida::serializar() {
    std::vector<char> infoAux;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->obtenerId());
    infoAux.insert(infoAux.end(), aux.begin(), aux.end());
    infoAux.insert(infoAux.end(), this->informacion.begin(), this->informacion.end());
    return infoAux;
}

void ActualizacionInicioPartida::deserializar(std::vector<char> &serializado) {
    std::vector<char> estadoJuegoSerializado(serializado.begin(),
                                             serializado.end());
    this->estadoJuego.deserializar(estadoJuegoSerializado);
}

EstadoJuego &ActualizacionInicioPartida::obtenerEstadoJuego() {
    return this->estadoJuego;
}
