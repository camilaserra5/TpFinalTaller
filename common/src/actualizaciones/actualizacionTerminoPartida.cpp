#include "actualizaciones/actualizacionTerminoPartida.h"
#include "estadoJuego.h"
ActualizacionTerminoPartida::ActualizacionTerminoPartida(EstadoJuego& estadoJuego):
        estadoJuego(estadoJuego){}

ActualizacionTerminoPartida::~ActualizacionTerminoPartida() {}

std::vector<char> ActualizacionTerminoPartida::serializar() {
    std::vector<char> informacion;
    return informacion;
}

void ActualizacionTerminoPartida::deserializar(std::vector<char> &serializado) {

}

std::vector<int> ActualizacionTerminoPartida::obtenerRanking() {
    std::vector<int> ranking;
    return ranking;
}
