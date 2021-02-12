#include "comandos/ataque.h"
#include "actualizaciones/actualizacionAtaque.h"
std::vector<Actualizacion *>  Ataque::ejecutar(EstadoJuego &estadoJuego) {
    Actualizacion* actualizacion = estadoJuego.realizarAtaque(this->idJugador);
    std::vector<Actualizacion *> actualizaciones;
    if (actualizacion != NULL){
      actualizaciones.push_back(actualizacion);
    }
    return actualizaciones;
}

Ataque::Ataque(int idJugador) : Comando(idJugador) {}

Ataque::~Ataque() {}

std::vector<char> Ataque::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(idJugador);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(static_cast<int>(Accion::ataque));
    informacion.insert(informacion.end(), aux.begin(), aux.end());

    return informacion;
}

void Ataque::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->idJugador = charArrayToNumber(sub);
}
