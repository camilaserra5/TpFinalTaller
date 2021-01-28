#include "../include/parser.h"

Parser::Parser(std::string file) {
    config = YAML::LoadFile(file);
}

std::string Parser::obtenerPuerto() {
    return config["port"].as<std::string>();
}


Parser::~Parser() {

}