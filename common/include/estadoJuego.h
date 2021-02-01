#ifndef _ESTADOJUEGO_H
#define _ESTADOJUEGO_H

#include "map.h"
#include "jugador.h"
#include <map>
#include <string>
#include "armas/arma.h"
#include "iserializable.h"

#define CANTIDAD_TOP_JUGADORES 5

class EstadoJuego : public ISerializable {
public:
    EstadoJuego(Map *mapa);

    ~EstadoJuego();

    void rotar(int idJugador);

    void moverse_a_derecha(int idJugador);

    void moverse_a_izquierda(int idJugador);

    void moverse_arriba(int idJugador);

    void moverse_abajo(int idJugador);

    void no_me_muevo(int idJugador);

    void agregarJugador(std::string &nombreJugador, int &id);

    void realizarAtaque(int idJugador);

    std::vector<char> serializar() {
        std::vector<char> informacion;
        informacion.push_back(jugadores.size());
        std::map<int, Jugador *>::iterator it;
        for (it = jugadores.begin(); it != jugadores.end(); ++it) {
            Jugador jugador = *it->second;
            std::vector<char> jugadorSerializado = jugador.serializar();
            informacion.insert(informacion.end(), jugadorSerializado.begin(), jugadorSerializado.end());
        }

        std::vector<char> mapaSerializado = mapa->serializar();
        informacion.insert(informacion.end(), mapaSerializado.begin(), mapaSerializado.end());
        return informacion;
    }

    void deserializar(std::vector<char>& informacion) {
        char jugadoresSize = informacion[0];
        int ult = 1;
        for (int i = 0; i < jugadoresSize; i++) {
            std::vector<char> jugadorSerializado(informacion.begin() + ult,
                                                 informacion.begin() + ult + 3);
            Jugador *jugador;
            jugador->deserializar(jugadorSerializado);
            this->jugadores.insert(std::make_pair(jugador->getId(), jugador));
            ult = ult + 3;
        }

        std::vector<char> mapaSerializado(informacion.begin() + ult,
                                          informacion.end());
        this->mapa->deserializar(mapaSerializado);
    }

    void verificarJugadoresMuertos();

    void buscarItemsEnPosJugador(Jugador *jugador, int &posX, int &posY, int xFinal, int yFinal);

    void abrirPuerta(int idJugador);


private:
    Map *mapa;
    std::map<int, Jugador *> jugadores;
};

#endif
