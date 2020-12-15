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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir mapa existente"), "",
                                                    tr("YAML Files (*.yaml *.yml)"));
    Map map = MapTranslator::yamlToMap(YAML::LoadFile(fileName.toStdString()));
    mapWidget = new MapWidget(mapWidget->tileSize() * map.getColSize(), mapWidget->tileSize() * map.getRowSize());
    mapTilesList = new MapTilesList(mapWidget->tileSize(), this);

    QFrame *frame = new QFrame;
    QHBoxLayout *mapLayout = new QHBoxLayout(frame);
    mapLayout->addWidget(mapTilesList);
    mapLayout->addWidget(mapWidget);

    setCentralWidget(frame);

    initTiles();

    for (int i = 0; i < map.getColSize(); ++i) {
        for (int j = 0; j < map.getRowSize(); ++j) {
            Type type = map(i, j);
            if (Type::wall == type) {
                QPoint point(i * mapWidget->tileSize(), j * mapWidget->tileSize());
                QPixmap newImage;
                newImage.load(QStringLiteral("../../editor/resources/wall1.jpg"));
                QPixmap pixmap = newImage.scaled(mapWidget->tileSize(), mapWidget->tileSize());
                mapWidget->addTile(point, pixmap, static_cast<int >(map(i, j)));
            } else if (Type::door == type) {
                QPoint point(i * mapWidget->tileSize(), j * mapWidget->tileSize());
                QPixmap newImage;
                newImage.load(QStringLiteral("../../editor/resources/wall2.jpg"));
                QPixmap pixmap = newImage.scaled(mapWidget->tileSize(), mapWidget->tileSize());
                mapWidget->addTile(point, pixmap, static_cast<int >(map(i, j)));
            } else if (Type::fakeDoor == type) {
                QPoint point(i * mapWidget->tileSize(), j * mapWidget->tileSize());
                QPixmap newImage;
                newImage.load(QStringLiteral("../../editor/resources/wall3.jpg"));
                QPixmap pixmap = newImage.scaled(mapWidget->tileSize(), mapWidget->tileSize());
                mapWidget->addTile(point, pixmap, static_cast<int >(map(i, j)));
            }
        }
    }
}

void MainWindow::newMap() {
    QDialog *d = new QDialog();
    QVBoxLayout *vbox = new QVBoxLayout();

    QLabel *widthLabel = new QLabel("Ancho:");
    widthLabel->setFixedWidth(50);
    QSpinBox *widthSpinbox = new QSpinBox;
    widthSpinbox->setRange(1, 1000);
    widthSpinbox->setSingleStep(1);
    widthSpinbox->setFixedWidth(50);
    widthSpinbox->setValue(10);

    QLabel *heightLabel = new QLabel("Alto:");
    heightLabel->setFixedWidth(50);
    QSpinBox *heightSpinbox = new QSpinBox;
    heightSpinbox->setRange(1, 1000);
    heightSpinbox->setSingleStep(1);
    heightSpinbox->setFixedWidth(50);
    heightSpinbox->setValue(10);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                       | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    vbox->addWidget(widthLabel);
    vbox->addWidget(widthSpinbox);
    vbox->addWidget(heightLabel);
    vbox->addWidget(heightSpinbox);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if (result == QDialog::Accepted) {
        mapWidget = new MapWidget(mapWidget->tileSize() * widthSpinbox->value(),
                                  mapWidget->tileSize() * heightSpinbox->value());
        mapTilesList = new MapTilesList(mapWidget->tileSize(), this);

        QFrame *frame = new QFrame;
        QHBoxLayout *mapLayout = new QHBoxLayout(frame);
        mapLayout->addWidget(mapTilesList);
        mapLayout->addWidget(mapWidget);

        setCentralWidget(frame);

        initTiles();
    }
}

void MainWindow::initTiles() {
    addTile(QStringLiteral("../../editor/resources/wall1.jpg"), Type::wall);
    addTile(QStringLiteral("../../editor/resources/wall2.jpg"), Type::door);
    addTile(QStringLiteral("../../editor/resources/wall3.jpg"), Type::fakeDoor);
}

void MainWindow::saveMap() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Guardar Mapa"), "", tr("YAML files (*.yaml *.yml)"));
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

    QAction *newAction = fileMenu->addAction(tr("&Nuevo..."), this, &MainWindow::newMap);
    newAction->setShortcuts(QKeySequence::New);

    QAction *openAction = fileMenu->addAction(tr("&Abrir..."), this, &MainWindow::openMap);
    openAction->setShortcuts(QKeySequence::Open);

    QAction *saveAction = fileMenu->addAction(tr("&Guardar"), this, &MainWindow::saveMap);
    saveAction->setShortcuts(QKeySequence::Save);

    QAction *exitAction = fileMenu->addAction(tr("&Salir"), qApp, &QCoreApplication::quit);
    exitAction->setShortcuts(QKeySequence::Quit);
}

void MainWindow::setupWidgets() {
    mapWidget = new MapWidget(400, 400);
    mapTilesList = new MapTilesList(mapWidget->tileSize(), this);
    QObject::connect(mapTilesList, SIGNAL(tileDoubleClicked(int, QPixmap)), mapWidget, SLOT(onTileDoubleClicked(int, QPixmap)));
    QFrame *frame = new QFrame;
    QHBoxLayout *mapLayout = new QHBoxLayout(frame);
    mapLayout->addWidget(mapTilesList);
    mapLayout->addWidget(mapWidget);

    setCentralWidget(frame);
}

MainWindow::~MainWindow() {

}