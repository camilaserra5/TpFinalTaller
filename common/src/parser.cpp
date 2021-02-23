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

int Parser::obtenerAltoPantallaJuego() {
    return this->config["screenHeightGame"].as<int>();
}

ConfiguracionPartida Parser::obtenerParametrosDeConfiguracion() {
    float vRotacion = this->config["vRotacion"].as<float>();
    float vAvance = this->config["vAvance"].as<float>();
    int vidaMax = this->config["vidaMax"].as<int>();
    int balasPorRafagaAmetralladora = this->config["balasPorRafagaAmetralladora"].as<int>();
    int balasPorRafagaCanion = this->config["balasPorRafagaCanion"].as<int>();
    int balasPorRafagaPistola = this->config["balasPorRafagaPistola"].as<int>();
    int maxBalas = this->config["maxBalas"].as<int>();
    int cantidadBalasInicial = this->config["cantidadBalasInicial"].as<int>();
    float distanciaMaxAcuchillable = this->config["distanciaMaxAcuchillable"].as<float>();
    float puntos_cruz = this->config["puntos_cruz"].as<float>();
    float punto_copa = this->config["punto_copa"].as<float>();
    float punto_cofre = this->config["punto_cofre"].as<float>();
    float puntos_corona = this->config["puntos_corona"].as<float>();
    int cantidadVidas = this->config["cantidadVidas"].as<int>();
    int puntosMatar = this->config["puntos_matar"].as<int>();
    int puntosBalas = this->config["puntos_balas"].as<int>();
    int danio_maximo_arma = this->config["danio_maximo_arma"].as<int>();
    ConfiguracionPartida config;
    config.setVRotacion(vRotacion);
    config.setVAvance(vAvance);
    config.setVidaMax(vidaMax);
    config.setBalasPorRafagaAmetralladora(balasPorRafagaAmetralladora);
    config.setBalasPorRafagaCanion(balasPorRafagaCanion);
    config.setBalasPorRafagaPistola(balasPorRafagaPistola);
    config.setMaxBalas(maxBalas);
    config.setCantidadBalasInicial(cantidadBalasInicial);
    config.setDistanciaMaxAcuchillable(distanciaMaxAcuchillable);
    config.setPuntos_cruz(puntos_cruz);
    config.setPunto_copa(punto_copa);
    config.setPunto_cofre(punto_cofre);
    config.setPuntos_corona(puntos_corona);
    config.setCantidadVidas(cantidadVidas);
    config.setPuntosMatar(puntosMatar);
    config.setPuntosBalas(puntosBalas);
    config.setDanioMaximoArma(danio_maximo_arma);

    return config;
}
