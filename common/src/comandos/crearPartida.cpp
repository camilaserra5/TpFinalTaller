#include "comandos/crearPartida.h"

std::vector<char> CrearPartida::serializar(){
  std::vector<char> info;
  info.push_back(static_cast<int>(Accion::crearPartida));
  info.push_back(this->cantidadJugadores);
  info.push_back(this->nombrePartida.size());
  info.insert(info.end(), this->nombrePartida.begin(), this->nombrePartida.end());
  info.push_back(this->rutaYaml.size());
  info.insert(info.end(), this->rutaYaml.begin(), this->rutaYaml.end());
  info.push_back(this->nombreCliente.size());
  info.insert(info.end(), this->nombreCliente.begin(), this->nombreCliente.end());
  return info;
}

void CrearPartida::deserializar(std::vector<char>& serializado){
  int idx = 1;
  this->cantidadJugadores = serializado[idx];
  idx += 1;
  int tamNombrePartida = serializado[idx];
  idx += 1;
  int i = tamNombrePartida + idx;
  while (idx < i){
    this->nombrePartida.push_back(serializado[idx]);
    idx += 1;
  }
  int tamRutaYaml = serializado[idx];
  idx += 1;
  i = idx + tamRutaYaml;
  while (idx < i){
    this->rutaYaml.push_back(serializado[idx]);
    idx += 1;
  }
  int tamNombreCliente = serializado[idx];
  i = idx + tamNombreCliente;
  while (idx <i){
    this->nombreCliente.push_back(serializado[idx]);
    idx += 1;
  }
}
std::string& CrearPartida::getNombreJugador(){
  return this->nombreCliente;
}

std::string& CrearPartida::getNombrePartida(){
  return this->nombrePartida;
}

int& CrearPartida::getCantJugadores(){
  return this->cantidadJugadores;
}

std::string& CrearPartida::getRutaArchivo(){
  return this->rutaYaml;
}
