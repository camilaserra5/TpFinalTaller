#include "actualizaciones/actualizacionInicioPartida.h"
#include "estadoJuego.h"

ActualizacionInicioPartida::ActualizacionInicioPartida(EstadoJuego &estadoJuego) :
        estadoJuego(estadoJuego), termine(false), rankingJugadores() {
    estadoJuego.verificarJugadoresMuertos();
    this->termine = this->estadoJuego.terminoPartida();
    Ranking ranking;
    this->rankingJugadores = ranking.obtenerTopJugadores(5,
                                                         estadoJuego.obtenerJugadores());
}

ActualizacionInicioPartida::~ActualizacionInicioPartida() {

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
    //  std::cerr << "actualizacion deserializar fin" << std::endl;
}

EstadoJuego &ActualizacionInicioPartida::obtenerEstadoJuego() {
    return this->estadoJuego;
}
