#include "editor.h"
#include <fstream>
#include <iostream>
void Editor::cargar_mapa(char** mapa, int tam_fila, int tam_columna){

}

void Editor::CrearMapa(std::string& nombre_archivo){
    YAML::Emitter yaml;
    yaml << YAML::BeginSeq;

    yaml << YAML::BeginMap;
    yaml << YAML::Key << "ancho" << YAML::Value << "500";
    yaml << YAML::Key << "largo" << YAML::Value << "500";
    yaml << YAML::Key << "nivel" << YAML::Value << "1";
    yaml << YAML::EndMap;

    if(std::ifstream(nombre_archivo)){
        std::cout << "archivo ya existe";
    }
    std::ofstream archivo(nombre_archivo);
    archivo << yaml.c_str();
    archivo.close();
}
