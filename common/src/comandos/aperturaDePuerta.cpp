#include "comandos/aperturaDePuerta.h"

void AperturaDePuerta::ejecutar(EstadoJuego &estadoJuego){
    estadoJuego.abrirPuerta(idJugador);
}
