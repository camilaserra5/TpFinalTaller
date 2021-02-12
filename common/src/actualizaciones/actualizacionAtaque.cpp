#include "actualizaciones/actualizacionAtaque.h"


ActualizacionAtaque::ActualizacionAtaque(Jugador* jugador,
                                  std::map<int, Jugador*>& jugadoresAtacados):
                                  jugador(jugador),
                                  jugadoresAtacados(jugadoresAtacados) {}


ActualizacionAtaque::~ActualizacionAtaque() {}

std::vector<char> ActualizacionAtaque::serializar() {
    std::vector<char> informacion;
    return informacion;
}

void ActualizacionAtaque::deserializar(std::vector<char> &serializado) {

}
