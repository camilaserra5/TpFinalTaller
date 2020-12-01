#ifndef EDITOR_H
#define EDITOR_H
#include <yaml-cpp/yaml.h>
#include <string>
class Editor{
  private:
    YAML::Node archivo;
    char mapa [10][10];
  public:
    Editor(){
      this->archivo = YAML::LoadFile("config.yaml");
    }
    void cargar_mapa(char** mapa, int tam_fila, int tam_columna);
    void mostrar_mapa();
    void CrearMapa(std::string& nombre_archivo);
    ~Editor();
};

#endif
