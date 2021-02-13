#include "comandos/movimiento.h"

#include "actualizaciones/actualizacionMovimiento.h"
#include "objetosJuego.h"

Movimiento::Movimiento(int &idJugador, Accion tipo_de_movimiento) :
        Comando(idJugador),
        tipo_de_movimiento(tipo_de_movimiento) {}

Movimiento::~Movimiento() {}

Movimiento::Movimiento() {}

std::vector<Actualizacion *> Movimiento::ejecutar(EstadoJuego &estadoJuego) {
    Actualizacion* actualizacion = nullptr;
    std::vector<Actualizacion *> actualizaciones;
    if (tipo_de_movimiento == Accion::rotarDerecha) {
        actualizacion = estadoJuego.rotar_a_derecha(this->idJugador);
    } else if (tipo_de_movimiento == Accion::rotarIzquierda) {
        actualizacion = estadoJuego.rotar_a_izquierda(this->idJugador);
    } else if (tipo_de_movimiento == Accion::moverArriba) {
        actualizaciones = estadoJuego.moverse_arriba(this->idJugador);
    } else if (tipo_de_movimiento == Accion::moverAbajo) {
        actualizaciones = estadoJuego.moverse_abajo(this->idJugador);
    }
    if (actualizacion != nullptr){
        actualizaciones.push_back(actualizacion);
    }
    return actualizaciones;
}

std::vector<char> Movimiento::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(idJugador);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(static_cast<int>(this->tipo_de_movimiento));
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    return informacion;
}

void Movimiento::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->idJugador = charArrayToNumber(sub);

    idx += 4;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->tipo_de_movimiento = static_cast<Accion>(charArrayToNumber(sub));
}
