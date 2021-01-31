#include "../include/comandos/rotacion.h"

void Rotacion::deserializar(std::vector<char>& serializado) {

}

void Rotacion::ejecutar(EstadoJuego &estadoJuego){
  estadoJuego.rotar(this->idJugador);
}
