#include "comandos/ataque.h"

void Ataque::ejecutar(EstadoJuego &estadoJuego) {
    estadoJuego.realizarAtaque(this->idJugador);
}

Ataque::Ataque(int idJugador) : Comando(idJugador) {}

Ataque::~Ataque() {}

std::vector<char> Ataque::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(static_cast<int>(Accion::ataque));
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(idJugador);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    return informacion;
}

void Ataque::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->idJugador = charArrayToNumber(sub);
}
