#include <QApplication>
#include "editor.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget ventana;
    //

    QHBoxLayout configuracion(&ventana);
    QVBoxLayout editar(&ventana);
    // Creo los widgets
    QLabel label("configuracion");
    QPushButton colores("editar colores");
    QPushButton personajes("editar personajes");
    // Agrego los widgets al layout vertical
    editar.addWidget(&label);
    editar.addWidget(&colores);
    editar.addWidget(&personajes);
    //configuracion.addH(&editar);
  //  QLabel label("El mapa a editar es\n");
    ventana.setLayout(&configuracion);
    ventana.setLayout(&editar);
    editar.show();
    ventana.show();
    return app.exec();
}
