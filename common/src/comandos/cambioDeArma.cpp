#include "../include/comandos/cambioDeArma.h"

void CambioDeArma::ejecutar(EstadoJuego &estadoJuego){
    estadoJuego.cambiarArma(idJugador);
}

std::vector<char> CambioDeArma::serializar(){
  std::vector<char> info;
  return info;
}

void CambioDeArma::deserializar(std::vector<char> &serializado){}
