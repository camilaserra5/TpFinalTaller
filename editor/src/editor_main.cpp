#include <QApplication>
#include "editor.h"
#include <QLabel>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget ventana;
    //

    QHBoxLayout configuracion(&ventana);
    QVBoxLayout editar(&configuracion);
    // Creo los widgets
    QLabel label("configuracion");
    QPushButton colores("editar colores");
    QPushButton personajes("editar personajes");
    // Agrego los widgets al layout vertical
    editar.addWidget(&label);
    editar.addWidget(&colores);
    editar.addWidget(&personajes);
    configuracion.addWidget(editar);
  //  QLabel label("El mapa a editar es\n");
    ventana.show();
    return app.exec();
}
