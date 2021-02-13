#include "actualizaciones/actualizacionAtaque.h"


ActualizacionAtaque::ActualizacionAtaque(Jugador *jugador,
                                         std::map<int, Jugador *> &jugadoresAtacados) :
        jugador(jugador),
        jugadoresAtacados(jugadoresAtacados) {}


ActualizacionAtaque::~ActualizacionAtaque() {}


std::vector<char> ActualizacionAtaque::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->obtenerId());
    informacion.insert(informacion.end(), aux.begin(), aux.end());

    std::vector<char> jugadorSerializado = jugador->serializar();
    aux = numberToCharArray(jugadorSerializado.size());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    informacion.insert(informacion.end(), jugadorSerializado.begin(), jugadorSerializado.end());

    std::map<int, Jugador *>::iterator it;
    for (it = jugadoresAtacados.begin(); it != jugadoresAtacados.end(); ++it) {
        Jugador jug = *it->second;
        jugadorSerializado = jug.serializar();
        aux = numberToCharArray(jugadorSerializado.size());
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        informacion.insert(informacion.end(), jugadorSerializado.begin(), jugadorSerializado.end());
    }
    return informacion;
}

void ActualizacionAtaque::deserializar(std::vector<char> &serializado) {
    std::vector<char> sub(4);
    int idx = 0;
    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    idx += 4;
    std::vector<char> jugadorSerializ(serializado.begin() + idx, serializado.begin() + idx + charArrayToNumber(sub));
    idx += charArrayToNumber(sub);
    jugador = new Jugador();
    jugador->deserializar(jugadorSerializ);

    sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
    int jugadoresSize = charArrayToNumber(sub);
    idx += 4;
    for (int i = 0; i < jugadoresSize; i++) {
        sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
        idx += 4;
        std::vector<char> jugadorSerializado(serializado.begin() + idx,
                                             serializado.begin() + idx + charArrayToNumber(sub));
        idx += charArrayToNumber(sub);
        auto jugadorAtacado = new Jugador();
        jugadorAtacado->deserializar(jugadorSerializado);
        this->jugadoresAtacados.insert(std::make_pair(jugadorAtacado->getId(), jugadorAtacado));
    }

}
