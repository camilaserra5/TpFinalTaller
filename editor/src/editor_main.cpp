#include <string>
#include <iostream>
#include <fstream>

#include "../include/mainwindow.h"
#include "map.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.initTiles();
    window.show();
    return app.exec();
}
