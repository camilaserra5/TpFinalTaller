#ifndef ACTUALIZACION_H
#define ACTUALIZACION_H

#include "estadoJuego.h"
#include <list>
#include "iserializable.h"
#include "ranking.h"

class Actualizacion : public ISerializable {
public:
    Actualizacion() {}

    Actualizacion(EstadoJuego &estadoJuego) :
            estadoJuego(estadoJuego), termine(false), rankingJugadores() {
        estadoJuego.verificarJugadoresMuertos();
        this->termine = this->estadoJuego.terminoPartida();
        Ranking ranking;
        this->rankingJugadores = ranking.obtenerTopJugadores(5, estadoJuego.obtenerJugadores());
    }

    std::vector<char> serializar() override {
        std::vector<char> informacion;
        std::vector<char> aux(4);
        aux = numberToCharArray(termine);
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        aux = numberToCharArray(this->rankingJugadores.size());
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        for (int rankingJugadore : this->rankingJugadores) {
            informacion.push_back(rankingJugadore);
        }
        std::vector<char> infoJuego = this->estadoJuego.serializar();
        informacion.insert(informacion.end(), infoJuego.begin(), infoJuego.end());
        return informacion;
    }

    void deserializar(std::vector<char> &serializado) override {
        this->termine = (bool) serializado[0];
        int cantRanking = (int) serializado[1];
        int idx = 2;
        for (int i = 0; i < cantRanking; i++) {
            this->rankingJugadores[i] == serializado[idx];
            idx++;
        }
        std::vector<char> estadoJuegoSerializado(serializado.begin() + idx,
                                                 serializado.end());
        this->estadoJuego.deserializar(estadoJuegoSerializado);
    }

    EstadoJuego &obtenerEstadoJuego() {
        return this->estadoJuego;
    }

    std::vector<int> obtenerRanking() {
        return this->rankingJugadores;
    }

    bool terminoPartida() {
        return termine;
    }

private:
    EstadoJuego estadoJuego;
    std::vector<int> rankingJugadores;
    bool termine;
};

#endif
