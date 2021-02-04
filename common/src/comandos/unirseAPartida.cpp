#include "comandos/unirseAPartida.h"

std::vector<char> UnirseAPartida::serializar(){
  std::vector<char> info;
  info.push_back(static_cast<int>(Accion::unirseAPartida));
  info.push_back(this->nombrePartida.size());
  info.insert(info.end(), this->nombrePartida.begin(), this->nombrePartida.end());
  info.push_back(this->nombreCliente.size());
  info.insert(info.end(), this->nombreCliente.begin(), this->nombreCliente.end());
  return info;
}

void UnirseAPartida::deserializar(std::vector<char>& serializado){
  int idx = 1;
  int tamNombrePartida = serializado[idx];
  idx++;
  while (idx < tamNombrePartida + 1){
    this->nombrePartida.push_back(serializado[idx]);
    idx++;
  }
  int tamNombreCliente = serializado[idx];
  idx++;
  while (idx < tamNombreCliente + 1){
    this->nombreCliente.push_back(serializado[idx]);
    idx++;
  }
}

std::string& UnirseAPartida::getNombreJugador(){
  return this->nombreCliente;
}

std::string& UnirseAPartida::getNombrePartida(){
  return this->nombrePartida;
}
