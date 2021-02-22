#include "actualizaciones/actualizacionInicioPartida.h"

ActualizacionInicioPartida::ActualizacionInicioPartida(EstadoJuego &estadoJuego) :
        estadoJuego(estadoJuego){
}

ActualizacionInicioPartida::~ActualizacionInicioPartida() {
  std::cerr << "entro al destructor de actalizacion inicializo partida\n";
}

std::vector<char> ActualizacionInicioPartida::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->obtenerId());
    informacion.insert(informacion.end(), aux.begin(), aux.end());

    std::vector<char> infoJuego = this->estadoJuego.serializar();
    informacion.insert(informacion.end(), infoJuego.begin(), infoJuego.end());
    return informacion;
}

void ActualizacionInicioPartida::deserializar(std::vector<char> &serializado) {
    std::vector<char> estadoJuegoSerializado(serializado.begin(),
                                             serializado.end());
    this->estadoJuego.deserializar(estadoJuegoSerializado);
}

EstadoJuego &ActualizacionInicioPartida::obtenerEstadoJuego() {
    return this->estadoJuego;
}
