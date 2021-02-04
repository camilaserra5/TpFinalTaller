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
  this->cantidadJugadores = (int)serializado[idx];
  std::cout << "cant jugadores " << this->cantidadJugadores <<'\n';
  idx += 1;

  int tamNombrePartida = serializado[idx];
  std::cout << "tamNombrePartida " << tamNombrePartida <<'\n';
  idx += 1;

  int i = tamNombrePartida + 1 + idx;
  std::cout << "i " << i <<'\n';

  while (idx < i){
    this->nombrePartida.push_back(serializado[idx]);
    idx += 1;
    std::cout << "entre al while\n";
  }
  std::cout << "nombrePartida " << this->nombrePartida <<'\n';
  std::cout << "i " << i <<'\n';


  int tamRutaYaml = (int)serializado[idx];
  i = idx + tamRutaYaml + 1;
  while (idx < i){
    this->rutaYaml.push_back(serializado[idx]);
    idx += 1;
  }
  std::cout << "i " << i <<'\n';

  std::cout << "rutaYaml " << this->rutaYaml <<'\n';

  int tamNombreCliente = (int)serializado[idx];
  i = idx + tamNombreCliente + 1;

  while (idx <i){
    this->nombreCliente.push_back(serializado[idx]);
    idx += 1;
  }
  std::cout << "nombreCliente " << this->nombreCliente <<'\n';

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
