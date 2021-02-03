#ifndef ACTUALIZACION_H
#define ACTUALIZACION_H

#include "estadoJuego.h"
#include <list>
#include "iserializable.h"
#include "ranking.h"

class Actualizacion : public ISerializable {
public:
    Actualizacion(EstadoJuego &estadoJuego) :
            estadoJuego(estadoJuego),termine(false), rankingJugadores() {
        estadoJuego.verificarJugadoresMuertos();
        this->termine = this->estadoJuego.terminoPartida();
        Ranking ranking;
        this->rankingJugadores = ranking.obtenerTopJugadores(5, estadoJuego.obtenerJugadores());
    }

    std::vector<char> serializar() override {
        std::vector<char> informacion;
        informacion.push_back(termine);
        informacion.push_back(this->rankingJugadores.size());
        for (int i = 0; i<this->rankingJugadores.size(); i++){
            informacion.push_back(this->rankingJugadores[i]);
        }
        std::vector<char> infoJuego = this->estadoJuego.serializar();
        informacion.insert(informacion.end(), infoJuego.begin(), infoJuego.end());
        return informacion;
    }

    void deserializar(std::vector<char> &serializado) override {
        this->termine = (bool)serializado[0];
        int cantRanking = (int)serializado[1];
        int idx = 2;
        for (int i = 0; i< cantRanking; i++){
              this->rankingJugadores[i] == serializado[idx];
              idx++;
        }
        std::vector<char> estadoJuegoSerializado(serializado.begin() + idx,
                                                           serializado.end());
        this->estadoJuego.deserializar(estadoJuegoSerializado);
    }
    EstadoJuego obtenerEstadoJuego(){
        return this->estadoJuego;
    }
    std::vector<int> obtenerRanking(){
        return this->rankingJugadores;
    }

    bool terminoPartida(){
        return termine;
    }

private:
    EstadoJuego &estadoJuego;
    std::vector<int> rankingJugadores;
    bool termine;
};

#endif
