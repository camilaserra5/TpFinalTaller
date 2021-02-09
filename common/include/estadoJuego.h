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
    EstadoJuego(Map& mapa);

    ~EstadoJuego();

    EstadoJuego();

    void rotar_a_derecha(int idJugador);

    void rotar_a_izquierda(int idJugador);

    void moverse_arriba(int idJugador);

    void moverse_abajo(int idJugador);

    void no_me_muevo(int idJugador);

    void agregarJugador(std::string &nombreJugador, int &id);

    void realizarAtaque(int idJugador);

    std::vector<char> serializar() override; 

    void deserializar(std::vector<char> &informacion) override;

    void verificarJugadoresMuertos();

    void verificarMovimientoJugador(Jugador *jugador, int &posX, int &posY);

    void abrirPuerta(int idJugador);

    std::map<int, Jugador *> &obtenerJugadores();
    Map& obtenerMapa();

    void lanzarContadorTiempoPartida();

    void actualizarTiempoPartida();

    bool terminoPartida();

    void cambiarArma(int idJugador);


private:
    Map mapa;
    std::map<int, Jugador *> jugadores;
    int contador;
    int jugadoresMuertos = 0;
};

#endif
