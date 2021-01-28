#ifndef _ESTADOJUEGO_H
#define _ESTADOJUEGO_H

#include "map.h"
#include "jugador.h"
#include <map>
#include <string>
#include "armas/arma.h"
#include "iserializable.h"

#define CANTIDAD_TOP_JUGADORES 5

class EstadoJuego : public ISerializable{
public:
    EstadoJuego(Map *mapa);

    ~EstadoJuego();

    void moverse_a_derecha(int idJugador);

    void moverse_a_izquierda(int idJugador);

    void moverse_arriba(int idJugador);

    void moverse_abajo(int idJugador);

    void no_me_muevo(int idJugador);

    void agregarJugador(std::string &nombreJugador, int &id);

    void realizarAtaque(int idJugador);

    std::stringstream serializar(){
        std::stringstream informacion;
        return informacion;
        //mapa->serializar();
    }
    void deserializar(){}

    void verificarJugadoresMuertos();

    void buscarItemsEnPosJugador(Jugador* jugador,int& posX,int& posY, int& xFinal, int& yFinal);


private:
    Map *mapa;
    std::map<int, Jugador *> jugadores;
};

#endif
