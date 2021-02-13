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

    aux = numberToCharArray(this->obtenerRanking().size());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    for (int rankingJugadore : this->obtenerRanking()) {
        aux = numberToCharArray(rankingJugadore);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
    }

    return informacion;
}

void ActualizacionTerminoPartida::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub;
    int elementosSize = charArrayToNumber(serializado);

    int idx = 0;
    for (int i = 0; i < elementosSize; i++) {
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        idx += 4;
        this->ranking.push_back(charArrayToNumber(sub));
    }
}

std::vector<int> ActualizacionTerminoPartida::obtenerRanking() {
    return this->ranking;
}
