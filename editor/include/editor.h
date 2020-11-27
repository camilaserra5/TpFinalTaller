#ifndef EDITOR_H
#define EDITOR_H
#include <yaml-cpp/yaml.h>

class Editor{
  private:
    YAML::Node archivo;
  public:
    Editor(){
      this->archivo = YAML::LoadFile("config.yaml");
    }
    void cargar_mapa(char** mapa, int tam_fila, int tam_columna);
    void mostrar_mapa();
    ~Editor();
};

#endif
