#include "actualizaciones/actualizacionTerminoPartida.h"
#include "estadoJuego.h"

ActualizacionTerminoPartida::ActualizacionTerminoPartida(EstadoJuego &estadoJuego) :
        estadoJuego(estadoJuego) {}

ActualizacionTerminoPartida::~ActualizacionTerminoPartida() {}


std::vector<char> ActualizacionTerminoPartida::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->obtenerId());
    informacion.insert(informacion.end(), aux.begin(), aux.end());

    std::vector<char> infoJuego = this->estadoJuego.serializar();
    informacion.insert(informacion.end(), infoJuego.begin(), infoJuego.end());
    return informacion;
}

void ActualizacionTerminoPartida::deserializar(std::vector<char> &serializado) {
    std::vector<char> estadoJuegoSerializado(serializado.begin(),
                                             serializado.end());
    this->estadoJuego.deserializar(estadoJuegoSerializado);
}

Ranking *ActualizacionTerminoPartida::obtenerRanking() {
    return new Ranking(this->estadoJuego.obtenerJugadores());
}
