#include <QApplication>
#include "editor.h"
#include <QLabel>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QLabel label("El mapa a editar es\n");
    label.show();
    return app.exec();
}
