#include "actualizaciones/actualizacionInicioPartida.h"

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
    aux = numberToCharArray(termine);
    informacion.insert(informacion.end(), aux.begin(), aux.end());

    aux = numberToCharArray(this->rankingJugadores.size());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    for (int rankingJugadore : this->rankingJugadores) {
        aux = numberToCharArray(rankingJugadore);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
    }
    std::vector<char> infoJuego = this->estadoJuego.serializar();
    informacion.insert(informacion.end(), infoJuego.begin(), infoJuego.end());
    return informacion;
}

void ActualizacionInicioPartida::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
//    std::cerr << "actualizacion deserializar empieza" << std::endl;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->termine = charArrayToNumber(sub);
//    std::cerr << "actualizacion deserializar termine:" << this->termine << std::endl;
    idx += 4;

    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    int elementosSize = charArrayToNumber(sub);
//    std::cerr << "actualizacion deserializar size rank"  << elementosSize<< std::endl;
    idx += 4;
    for (int i = 0; i < elementosSize; i++) {
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        idx += 4;
        //      std::cerr << "actualizacion deserializar rank push" << charArrayToNumber(sub)<< std::endl;
        this->rankingJugadores.push_back(charArrayToNumber(sub));
    }

    std::vector<char> estadoJuegoSerializado(serializado.begin() + idx,
                                             serializado.end());
    this->estadoJuego.deserializar(estadoJuegoSerializado);
    //  std::cerr << "actualizacion deserializar fin" << std::endl;
}

EstadoJuego &ActualizacionInicioPartida::obtenerEstadoJuego() {
    return this->estadoJuego;
}