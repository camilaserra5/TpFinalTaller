#include <QApplication>
#include "editor.h"


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QLabel label("Soy el editor\n");
    return app.exec();
}

/*
YAML::Emitter out;
for (int i = 0; i < M; i++){
  for (int j = 0; j < M; j++){
    std::stringstream fila;
    char fila_b[M] = "0";
    fila.write(fila,M);
  }
}
*/
