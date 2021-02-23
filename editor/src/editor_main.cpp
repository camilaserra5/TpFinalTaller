#include "../include/mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[]) {
    std::string path = "";
    if (argc > 1)
        path = argv[1];
    QApplication app(argc, argv);
    MainWindow window(path);
    window.initTiles();
    window.show();
    return app.exec();
}
