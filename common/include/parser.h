#ifndef WOLFSTEIN_PARSER_H
#define WOLFSTEIN_PARSER_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "configuracionPartida.h"

class Parser {
public:
    Parser(std::string file);

    std::string obtenerPuerto();

    std::map<std::string, std::string> obtenerMapas();

    ~Parser();

    std::string obtenerRutaMapas();

    int obtenerAnchoPantallaLogin();

    int obtenerAltoPantallaLogin();

    int obtenerAnchoPantallaJuego();

    ConfiguracionPartida obtenerParametrosDeConfiguracion();

private:
    YAML::Node config;
};


#endif //WOLFSTEIN_PARSER_H
