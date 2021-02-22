#ifndef MAP_TRANSLATOR_H
#define MAP_TRANSLATOR_H

#include "map.h"
#include <list>
#include <string>
#include <yaml-cpp/yaml.h>

namespace MapTranslator {
    /*
      * traduce de la clase mama pa un yaml
    */
    YAML::Node mapToYaml(Map &map);
    /*
      * traduce de un yaml a la clase mapa
    */  
    Map yamlToMap(YAML::Node yaml, int anchoPantalla, ConfiguracionPartida& configuracion);
};


#endif //MAP_TRANSLATOR_H
