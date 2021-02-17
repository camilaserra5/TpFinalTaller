#include "../include/ranking.h"
#include <iterator>
#include <algorithm>

Ranking::Ranking(std::map<int, Jugador *> jugadores) : jugadores(jugadores) {}

bool estaEnElTop(Jugador *jugador, int &posicion, std::map<int, Jugador *> &jugadores,
                 std::vector<int> &topJugadores, int &cantidadTopJugadores) {
    bool estaEnElTop = false;
    int i = 0;
    int cantJugadoresEnElTopActual = topJugadores.size();
    while (i < cantJugadoresEnElTopActual && !estaEnElTop) {
        if (jugador->obtenerLogro() > jugadores.at(topJugadores[i])->obtenerLogro()) {
            posicion = i;
            estaEnElTop = true;
        } else if (jugador->obtenerLogro() == jugadores.at(topJugadores[i])->obtenerLogro()) {
            posicion = i + 1;
            estaEnElTop = true;
        }
        i++;
    }
    if (cantJugadoresEnElTopActual < cantidadTopJugadores && estaEnElTop) {
        posicion = cantJugadoresEnElTopActual;
        estaEnElTop = true;
    }
    return estaEnElTop;
}

void ordenarEnPosicion(int id, int &posicion, std::vector<int> &topJugadores, int &cantidadTopJugadores) {
    std::vector<int>::iterator it;
    it = topJugadores.begin();
    topJugadores.insert(it + posicion, id);
    int cantJugadoresEnElTopActual = topJugadores.size();
    if (cantJugadoresEnElTopActual > cantidadTopJugadores) {
        topJugadores.resize(cantidadTopJugadores);
    }
}

std::vector<int> Ranking::obtenerTopJugadores(int cantidadTopJugadores) {
    std::map<int, Jugador *>::iterator it;
    std::vector<int> topJugadores;
    topJugadores.push_back(jugadores.begin()->first);
    int posicion = 0;
    for (it = jugadores.begin(); it != jugadores.end(); ++it) {
        if (estaEnElTop(it->second, posicion, jugadores, topJugadores, cantidadTopJugadores)) {
            ordenarEnPosicion(it->first, posicion, topJugadores, cantidadTopJugadores);
        }
    }
    return topJugadores;
}

std::vector<std::pair<int, Jugador *>> Ranking::obtenerTop5EnemigosMatados() {
    int n = std::min(5, (int) jugadores.size());
    std::vector<std::pair<int, Jugador *>> top(n);
    std::partial_sort_copy(jugadores.begin(),
                           jugadores.end(),
                           top.begin(),
                           top.end(),
                           [](std::pair<const int, Jugador *> const &l,
                              std::pair<const int, Jugador *> const &r) {
                               return l.second->obtenerLogro().obtenerEnemigosMatados() >
                                      r.second->obtenerLogro().obtenerEnemigosMatados();
                           });
    return top;
}

std::vector<std::pair<int, Jugador *>> Ranking::obtenerTop5PuntosTotalesPorTesoros() {
    int n = std::min(5, (int) jugadores.size());
    std::vector<std::pair<int, Jugador *>> top(n);
    std::partial_sort_copy(jugadores.begin(),
                           jugadores.end(),
                           top.begin(),
                           top.end(),
                           [](std::pair<const int, Jugador *> const &l,
                              std::pair<const int, Jugador *> const &r) {
                               return l.second->obtenerLogro().obtenerPuntosTotalesPorTesoros() >
                                      r.second->obtenerLogro().obtenerPuntosTotalesPorTesoros();
                           });
    return top;
}

std::vector<std::pair<int, Jugador *>> Ranking::obtenerTop5BalasDisparadas() {
    int n = std::min(5, (int) jugadores.size());
    std::vector<std::pair<int, Jugador *>> top(n);
    std::partial_sort_copy(jugadores.begin(),
                           jugadores.end(),
                           top.begin(),
                           top.end(),
                           [](std::pair<const int, Jugador *> const &l,
                              std::pair<const int, Jugador *> const &r) {
                               return l.second->obtenerLogro().obtenerBalasDisparadas() >
                                      r.second->obtenerLogro().obtenerBalasDisparadas();
                           });
    return top;
}
