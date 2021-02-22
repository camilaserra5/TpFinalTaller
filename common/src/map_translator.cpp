#include "../include/map_translator.h"

YAML::Node MapTranslator::mapToYaml(Map &map) {
    YAML::Node node;
    node["rows"] = map.getRowSize();
    node["cols"] = map.getColSize();
    for (std::size_t i = 0; i < map.getRowSize(); i++) {
        std::list<unsigned> v;
        for (std::size_t j = 0; j < map.getColSize(); j++) {
            v.push_back(map(i, j).getType());
        }
        node["map"].push_back(v);
    }

    return node;
}

Map MapTranslator::yamlToMap(YAML::Node yaml, int anchoPantalla,ConfiguracionPartida& configuracion) {
    const unsigned rows = yaml["rows"].as<unsigned>();
    const unsigned cols = yaml["cols"].as<unsigned>();

    Map map(rows, cols, anchoPantalla, configuracion);
    YAML::Node mapNode = yaml["map"];
    for (std::size_t i = 0; i < mapNode.size(); i++) {
        YAML::Node rowNode = mapNode[i];
        for (std::size_t j = 0; j < rowNode.size(); j++) {
            map.setValue(i, j, ObjetosJuego::obtenerTipoPorId(rowNode[j].as<unsigned>()));
        }
    }
    return std::move(map);
}
