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
    const YAML::Node &maps = config["mapas"];
    for (unsigned i = 0; i < maps.size(); i++) {
        mapas.insert(std::make_pair(maps[i]["name"].as<std::string>(), maps[i]["file"].as<std::string>()));
    }
    return mapas;
}

Parser::~Parser() {
//cerrar
}

std::string Parser::obtenerRutaMapas() {
    return this->config["rutaMapas"].as<std::string>();
}

int Parser::obtenerAnchoPantallaLogin() {
    return this->config["screenWidthLogin"].as<int>();
}

int Parser::obtenerAltoPantallaLogin() {
    return this->config["screenHeightLogin"].as<int>();
}

int Parser::obtenerAnchoPantallaJuego() {
    return this->config["screenWidthGame"].as<int>();
}
