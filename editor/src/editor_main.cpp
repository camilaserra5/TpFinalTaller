#include <QApplication>
#include "editor.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPalette>
#include <string>

int main(int argc, char *argv[]) {
    /*QApplication app(argc, argv);
    QWidget ventana;

    ventana.setGeometry(50,50,500,500);

    ventana.setStyleSheet("background-color: blue");
    QLabel label("configuracion");

    QPushButton colores("editar colores");
    QPushButton personajes("editar personajes");

    QHBoxLayout configuracion;
    QVBoxLayout editar;
    // Agrego los widgets al layout vertical y horiontal;
    configuracion.addWidget(&label);
    editar.addWidget(&colores);
    editar.addWidget(&personajes);
    //configuracion.addH(&editar);
  //  QLabel label("El mapa a editar es\n");
    //ventana.setLayout(&configuracion);
    ventana.setLayout(&editar);
    ventana.show();*/
    Editor editor;
    std::string nombre_archivo("mapa.txt");
    editor.CrearMapa(nombre_archivo);
    //return app.exec();
    return 0;
}
