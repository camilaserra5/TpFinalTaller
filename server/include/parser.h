#ifndef WOLFSTEIN_PARSER_H
#define WOLFSTEIN_PARSER_H

#include <string>
#include <yaml-cpp/yaml.h>

class Parser {
public:
    Parser(std::string file);

    std::string obtenerPuerto();

    ~Parser();

private:
    YAML::Node config;
};


#endif //WOLFSTEIN_PARSER_H
