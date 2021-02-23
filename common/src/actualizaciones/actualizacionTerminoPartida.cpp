#include "actualizaciones/actualizacionTerminoPartida.h"

ActualizacionTerminoPartida::ActualizacionTerminoPartida(std::map<int,Jugador*> jugadores) :
        jugadores(jugadores) {}

ActualizacionTerminoPartida::~ActualizacionTerminoPartida() {
  if (esCliente){
    std::map<int, Jugador *>::iterator it = this->jugadores.begin();
    while (it != this->jugadores.end()) {
        delete it->second;
        ++it;
    }
  }
}


std::vector<char> ActualizacionTerminoPartida::serializar() {
    std::vector<char> informacion;
    std::vector<char> aux(4);
    aux = numberToCharArray(this->obtenerId());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    std::map<int, Jugador *>::iterator it;
    aux = numberToCharArray(this->jugadores.size());
    informacion.insert(informacion.end(), aux.begin(), aux.end());
    std::vector<char> jugadorSerializado;
    for (it = jugadores.begin(); it != jugadores.end(); ++it) {
        jugadorSerializado = it->second->serializar();
        aux = numberToCharArray(jugadorSerializado.size());
        informacion.insert(informacion.end(), aux.begin(), aux.end());
        informacion.insert(informacion.end(), jugadorSerializado.begin(), jugadorSerializado.end());
    }
    return informacion;
}

void ActualizacionTerminoPartida::deserializar(std::vector<char> &serializado) {
  this->esCliente = true;
  int idx = 0;
  std::vector<char> sub;
  sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
  int jugadoresSize = charArrayToNumber(sub);
  idx += 4;
  for (int i = 0; i < jugadoresSize; i++) {
      sub = std::vector<char>(&serializado[idx], &serializado[idx + 4]);
      idx += 4;
      std::vector<char> jugadorSerializado(serializado.begin() + idx,
                                           serializado.begin() + idx + charArrayToNumber(sub));
      idx += charArrayToNumber(sub);
      Jugador *jugador = new Jugador();
      jugador->deserializar(jugadorSerializado);
      this->jugadores.insert(std::make_pair(jugador->getId(), jugador));
  }
}
