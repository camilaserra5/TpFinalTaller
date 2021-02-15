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

    Actualizacion* rotar_a_derecha(int idJugador);

    Actualizacion* rotar_a_izquierda(int idJugador);

    std::vector<Actualizacion*> moverse_arriba(int idJugador);

    std::vector<Actualizacion*> moverse_abajo(int idJugador);

    void no_me_muevo(int idJugador);

    void agregarJugador(std::string &nombreJugador, int &id);

    Actualizacion* realizarAtaque(int idJugador);

    std::vector<char> serializar() override;

    void deserializar(std::vector<char> &informacion) override;

    void verificarJugadoresMuertos();

    std::vector<Actualizacion*> verificarMovimientoJugador(Jugador *jugador, int &posX, int &posY);

    Actualizacion* abrirPuerta(int idJugador);

    std::map<int, Jugador *> &obtenerJugadores();
    Map& obtenerMapa();

    void lanzarContadorTiempoPartida();

    void actualizarTiempoPartida();

    bool terminoPartida();

    Actualizacion* cambiarArma(int idJugador);

private:
    Map mapa;
    std::map<int, Jugador *> jugadores;
    int contador;
    int jugadoresMuertos = 0;
};

#endif
