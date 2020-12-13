#include "../include/movimiento.h"

#define DERECHA 1
#define IZQUIERDA -1
#define ARRIBA 2
#define ABAJO -2

Movimiento::Movimiento(int &idJugador, int &tipo_de_movimiento) :
        idJugador(idJugador),
        tipo_de_movimiento(tipo_de_movimiento) {}

Movimiento::~Movimiento() {}

void Movimiento::estrategia(EstadoJuego &estadoJuego) {
    //van a ser las teclas cuando me muevo
    if (tipo_de_movimiento == DERECHA) {
        estadoJuego.moverse_a_derecha(this->idJugador);
    } else if (tipo_de_movimiento == IZQUIERDA) {
        estadoJuego.moverse_a_izquierda(this->idJugador);
    } else if (tipo_de_movimiento == ARRIBA) {
        estadoJuego.moverse_arriba(this->idJugador);
    } else if (tipo_de_movimiento == ABAJO) {
        estadoJuego.moverse_abajo(this->idJugador);
    } else {
        estadoJuego.no_me_muevo(this->idJugador);
    }
    std::cout << "me muevo lol\n";
}
