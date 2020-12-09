#include "../include/mainwindow.h"
#include "../include/map_tiles_list.h"
#include "../include/map_widget.h"
#include <string>
#include <iostream>
#include <fstream>
#include <QtWidgets>
#include "map.h"
#include "map_translator.h"
#include <yaml-cpp/yaml.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupMenus();
    setupWidgets();

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setWindowTitle(tr("Editor"));
    mapTilesList->clear();
    mapWidget->clear();
}

void MainWindow::openMap() {

}

void MainWindow::saveMap() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar Mapa"), "", tr("YAML files (*.yaml)"));
    Map map = mapWidget->toMap();

    YAML::Node yaml = MapTranslator::mapToYaml(map);
    YAML::Emitter emitter;
    emitter << yaml;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << QString::fromStdString(emitter.c_str());
    file.close();
}

void MainWindow::addTile(const QString &path, Type type) {
    QPixmap newImage;
    if (!newImage.load(path)) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No se pudo cargar el icono"),
                             QMessageBox::Close);
        return;
    }

    int tileSize = mapWidget->tileSize();
    QPixmap scaledImg = newImage.scaled(tileSize, tileSize);
    mapTilesList->addTile(scaledImg, type);
}


void MainWindow::setupMenus() {
    QMenu *fileMenu = menuBar()->addMenu(tr("&Archivo"));

    QAction *openAction = fileMenu->addAction(tr("&Abrir..."), this, &MainWindow::openMap);
    openAction->setShortcuts(QKeySequence::Open);

    QAction *saveAction = fileMenu->addAction(tr("&Guardar"), this, &MainWindow::saveMap);
    saveAction->setShortcuts(QKeySequence::Save);

    QAction *exitAction = fileMenu->addAction(tr("&Salir"), qApp, &QCoreApplication::quit);
    exitAction->setShortcuts(QKeySequence::Quit);
}

void MainWindow::setupWidgets() {
    QFrame *frame = new QFrame;
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);

    mapWidget = new MapWidget(400, 400);
    mapTilesList = new MapTilesList(mapWidget->tileSize(), this);

    frameLayout->addWidget(mapTilesList);
    frameLayout->addWidget(mapWidget);

    setCentralWidget(frame);
}

MainWindow::~MainWindow() {

}