#include "../include/map_translator.h"
#include <iostream>

YAML::Node MapTranslator::mapToYaml(Map &map) {
    YAML::Node node;
    node["rows"] = map.getRowSize();
    node["cols"] = map.getColSize();

    return node;
}

Map MapTranslator::yamlToMap(YAML::Node yaml) {
    const unsigned rows = yaml["rows"].as<unsigned>();
    const unsigned cols = yaml["cols"].as<unsigned>();

    Map map(rows, cols);
    //for (std::size_t i = 0; i < yaml["map"].size(); i++) {
    //std::cout << yaml["map"][i].as<int>() << "\n";
    //}
    return map;
}