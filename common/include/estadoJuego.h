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
    EstadoJuego();

    void rotar_a_derecha(int idJugador);

    void rotar_a_izquierda(int idJugador);

    void moverse_arriba(int idJugador);

    void moverse_abajo(int idJugador);

    void no_me_muevo(int idJugador);

    void agregarJugador(std::string &nombreJugador, int &id);

    void realizarAtaque(int idJugador);

    std::vector<char> serializar() override; /* {
        std::vector<char> informacion;
        std::vector<char> aux(4);
        aux = numberToCharArray(jugadores.size());
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        std::map<int, Jugador *>::iterator it;
        for (it = jugadores.begin(); it != jugadores.end(); ++it) {
            Jugador jugador = *it->second;
            std::vector<char> jugadorSerializado = jugador.serializar();
            aux = numberToCharArray(jugadorSerializado.size());
            informacion.insert(informacion.end(), aux.begin(), aux.end());
            informacion.insert(informacion.end(), jugadorSerializado.begin(), jugadorSerializado.end());
        }
        std::vector<char> mapaSerializado = mapa->serializar();
        informacion.insert(informacion.end(), mapaSerializado.begin(), mapaSerializado.end());
        return informacion;
    }*/

    void deserializar(std::vector<char>& informacion) override; /*{
        std::vector<char> sub(4);
        int idx = 0;
        sub = std::vector<char>(&informacion[idx], &informacion[idx + 4]);
        int jugadoresSize = charArrayToNumber(sub);
        idx += 4;
        for (int i = 0; i < jugadoresSize; i++) {
            sub = std::vector<char>(&informacion[idx], &informacion[idx + 4]);
            idx += 4;
            std::vector<char> jugadorSerializado(informacion.begin() + idx,
                                                 informacion.begin() + idx + charArrayToNumber(sub));
            idx += charArrayToNumber(sub);
            Jugador *jugador;
            jugador->deserializar(jugadorSerializado);
            this->jugadores.insert(std::make_pair(jugador->getId(), jugador));
        }
        std::vector<char> mapaSerializado(informacion.begin() + idx,
                                          informacion.end());
        this->mapa->deserializar(mapaSerializado);
    }*/

    void verificarJugadoresMuertos();

    void verificarMovimientoJugador(Jugador* jugador,int& posX,int& posY);

    void abrirPuerta(int idJugador);

    std::map<int, Jugador*>& obtenerJugadores(); /*{
        return this->jugadores;
    }*/
    Map* obtenerMapa();/*{
        return this->mapa;
    }*/

    void lanzarContadorTiempoPartida();

    void actualizarTiempoPartida();

    bool terminoPartida();

private:
    Map *mapa;
    std::map<int, Jugador *> jugadores;
    int contador;
    int jugadoresMuertos;
};

#endif
