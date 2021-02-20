#include "comandos/desconectarJugador.h"

DesconectarJugador::DesconectarJugador(int idJugador) : Comando(idJugador) {}

DesconectarJugador::~DesconectarJugador() {}

std::vector<Actualizacion *> DesconectarJugador::ejecutar(EstadoJuego &estadoJuego) {
    return estadoJuego.desconectarJugador(idJugador);
}

std::vector<char> DesconectarJugador::serializar() {
    std::vector<char> informacion;
    return informacion;
}

void DesconectarJugador::deserializar(std::vector<char> &serializado) {

}
