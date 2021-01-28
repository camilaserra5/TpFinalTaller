#include "comandos/ataque.h"

void Ataque::ejecutar(EstadoJuego &estadoJuego) {
    estadoJuego.realizarAtaque(this->idJugador);
}
/*
std::stringstream Ataque::serializar(){
    std::stringstream informacion;
    int tipo = static_cast<int>(Accion::ataque);
    informacion << tipo;
    informacion << this->idJugador;
    return informacion;
}
*/