#include "../include/parser.h"
#include<iostream>

Parser::Parser(std::string file) {
    this->config = YAML::LoadFile(file);
}

std::string Parser::obtenerPuerto() {
    return this->config["port"].as<std::string>();
}

std::map<std::string, std::string> Parser::obtenerMapas() {
  std::map<std::string, std::string> mapas;
  std::string nombreMapa = "mapa1";
  std::string rutaMapa = config["mapa1"].as<std::string>();
  mapas.insert(std::make_pair(nombreMapa,rutaMapa));
  nombreMapa = "mapa2";
  rutaMapa = config["mapa2"].as<std::string>();
  mapas.insert(std::make_pair(nombreMapa,rutaMapa));
  nombreMapa = "mapa4";
  rutaMapa = config["mapa4"].as<std::string>();
  mapas.insert(std::make_pair(nombreMapa,rutaMapa));
  nombreMapa = "mapa5";
  rutaMapa = config["mapa5"].as<std::string>();
  mapas.insert(std::make_pair(nombreMapa,rutaMapa));
  nombreMapa = "mapa6";
  rutaMapa = config["mapa6"].as<std::string>();
  mapas.insert(std::make_pair(nombreMapa,rutaMapa));
  std::cerr << nombreMapa << " y " << rutaMapa << "\n";
  return mapas;
}

Parser::~Parser() {
//cerrar
}

int Parser::obtenerAnchoPantallaLogin(){
  return this->config["screenWidthLogin"].as<int>();
}

int Parser::obtenerAltoPantallaLogin(){
  return this->config["screenHeightLogin"].as<int>();
}
