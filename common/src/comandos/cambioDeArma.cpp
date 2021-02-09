#include "../include/comandos/cambioDeArma.h"

void CambioDeArma::ejecutar(EstadoJuego &estadoJuego) {
    estadoJuego.cambiarArma(idJugador);
}

std::vector<char> CambioDeArma::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(static_cast<int>(Accion::cambioDeArma));
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(idJugador);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    return informacion;
}

void CambioDeArma::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->idJugador = charArrayToNumber(sub);
}
