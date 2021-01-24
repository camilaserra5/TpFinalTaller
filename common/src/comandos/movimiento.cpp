#include "comandos/movimiento.h"


#include "objetosJuego.h"

Movimiento::Movimiento(int &idJugador, Accion tipo_de_movimiento) :
        idJugador(idJugador),
        tipo_de_movimiento(tipo_de_movimiento) {}

Movimiento::~Movimiento() {}

void Movimiento::ejecutar(EstadoJuego &estadoJuego) {

    if (tipo_de_movimiento == Accion::moverDerecha) {
        estadoJuego.moverse_a_derecha(this->idJugador);
    } else if (tipo_de_movimiento == Accion::moverIzquierda) {
        estadoJuego.moverse_a_izquierda(this->idJugador);
    } else if (tipo_de_movimiento == Accion::moverArriba) {
        estadoJuego.moverse_arriba(this->idJugador);
    } else if (tipo_de_movimiento == Accion::moverAbajo) {
        estadoJuego.moverse_abajo(this->idJugador);
    } else {
        estadoJuego.no_me_muevo(this->idJugador);
    }
}

std::stringstream Movimiento::serializar(){
    std::stringstream informacion;
    informacion <<  static_cast<int>(this->tipo_de_movimiento);
    informacion << this->idJugador;
    return informacion;
}
