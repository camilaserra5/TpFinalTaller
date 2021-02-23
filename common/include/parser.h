#ifndef WOLFSTEIN_PARSER_H
#define WOLFSTEIN_PARSER_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "configuracionPartida.h"

class Parser {
public:
    /*
      * creara la clase parser dejandola valida para uso
    */
    Parser(std::string file);
    /*
      * devuelve el puerto
    */
    std::string obtenerPuerto();
    /*
      * devuelve los mapas
    */
    std::map<std::string, std::string> obtenerMapas();
    /*
      * liberara la clase
    */
    ~Parser();
    /*
      * devuelve la tta de los mapas
    */
    std::string obtenerRutaMapas();
    /*
      * devuelve el anhco de la pantalla log in
    */
    int obtenerAnchoPantallaLogin();
    /*
      * devuelve el alto de la pantala log in
    */
    int obtenerAltoPantallaLogin();
    /*
      * devuelve el ancho de la pantalla juego
    */
    int obtenerAnchoPantallaJuego();
    /*
      * devuelve el alto de la pantalla juego
    */
    int obtenerAltoPantallaJuego();
    /*
      * deuvleve los parametros de configiuracion
    */
    ConfiguracionPartida obtenerParametrosDeConfiguracion();

private:
    YAML::Node config;
};


#endif //WOLFSTEIN_PARSER_H
