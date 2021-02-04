#include "comandos/movimiento.h"


#include "objetosJuego.h"

Movimiento::Movimiento(int &idJugador, Accion tipo_de_movimiento) :
        Comando(idJugador),
        tipo_de_movimiento(tipo_de_movimiento) {}

Movimiento::~Movimiento() {}

void Movimiento::ejecutar(EstadoJuego &estadoJuego) {

    if (tipo_de_movimiento == Accion::rotarDerecha) {
        estadoJuego.rotar_a_derecha(this->idJugador);
    } else if (tipo_de_movimiento == Accion::rotarIzquierda) {
        estadoJuego.rotar_a_izquierda(this->idJugador);
    } else if (tipo_de_movimiento == Accion::moverArriba) {
        estadoJuego.moverse_arriba(this->idJugador);
    } else if (tipo_de_movimiento == Accion::moverAbajo) {
        estadoJuego.moverse_abajo(this->idJugador);
    } else {
        estadoJuego.no_me_muevo(this->idJugador);
    }
}
/*
std::stringstream Movimiento::serializar(){
    std::stringstream informacion;
    // vector concatenamos caracteres;

    std::vector<char> informacion;
    informacion.insert(static_cast<int>(this->tipo_de_movimiento));
    informacion.insert( this->idJugador);
    informacion <<  static_cast<int>(this->tipo_de_movimiento);
    informacion << this->idJugador;
    return informacion;
}
*/
