#include "comandos/aperturaDePuerta.h"
#include "actualizaciones/actualizacionAperturaPuerta.h"

AperturaDePuerta::AperturaDePuerta(int idJugador) : Comando(idJugador) {}

AperturaDePuerta::~AperturaDePuerta() {}

std::vector<Actualizacion *> AperturaDePuerta::ejecutar(EstadoJuego &estadoJuego) {
    estadoJuego.abrirPuerta(idJugador);
    std::vector<Actualizacion *> actualizaciones;
    actualizaciones.push_back(new ActualizacionAperturaPuerta());
    return actualizaciones;
}

std::vector<char> AperturaDePuerta::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(idJugador);
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    aux = numberToCharArray(static_cast<int>(Accion::aperturaDePuerta));
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    return informacion;
}

void AperturaDePuerta::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    this->idJugador = charArrayToNumber(sub);
}
