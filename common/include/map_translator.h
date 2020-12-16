#ifndef MAP_TRANSLATOR_H
#define MAP_TRANSLATOR_H

#include "map.h"
#include "entidadPosicionable.h"
#include <list>
#include <string>
#include <yaml-cpp/yaml.h>

namespace MapTranslator {
    YAML::Node mapToYaml(Map &map/*,std::list<EntidadPosicionable>& entidades*/);

    Map yamlToMap(YAML::Node yaml);
};


#endif //MAP_TRANSLATOR_H
