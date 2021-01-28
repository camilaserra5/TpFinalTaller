#include "../include/ranking.h"
#include <iterator>

bool estaEnElTop(Jugador *jugador, int &posicion, std::map<int, Jugador *> &jugadores,
                 std::vector<int> &topJugadores, int &cantidadTopJugadores) {
    bool estaEnElTop = false;
    int i = 0;
    while (i < topJugadores.size() && !estaEnElTop) {
        if (jugador->obtenerLogro() > jugadores.at(topJugadores[i])->obtenerLogro()) {
            posicion = i;
            estaEnElTop = true;
        } else if (jugador->obtenerLogro() == jugadores.at(topJugadores[i])->obtenerLogro()) {
            posicion = i + 1;
            estaEnElTop = true;
        }
        i++;
    }
    if (topJugadores.size() < cantidadTopJugadores && estaEnElTop) {
        posicion = topJugadores.size();
        estaEnElTop = true;
    }
    return estaEnElTop;
}

void ordenarEnPosicion(int id, int &posicion, std::vector<int> &topJugadores, int &cantidadTopJugadores) {
    std::vector<int>::iterator it;
    it = topJugadores.begin();
    topJugadores.insert(it + posicion, id);
    if (topJugadores.size() > cantidadTopJugadores) {
        topJugadores.resize(cantidadTopJugadores);
    }
}

std::vector<int> Ranking::obtenerTopJugadores(int cantidadTopJugadores, std::map<int, Jugador *> &jugadores) {
    std::map<int, Jugador *>::iterator it;
    std::vector<int> topJugadores;
    topJugadores[0] = jugadores.begin()->first;
    int posicion = 0;
    for (it = jugadores.begin(); it != jugadores.end(); ++it) {
        if (estaEnElTop(it->second, posicion, jugadores, topJugadores, cantidadTopJugadores)) {
            ordenarEnPosicion(it->first, posicion, topJugadores, cantidadTopJugadores);
        }
    }
    return topJugadores;
}
