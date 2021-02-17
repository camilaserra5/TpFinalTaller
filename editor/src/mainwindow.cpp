#include "../include/mainwindow.h"
#include "../include/map_tiles_list.h"
#include "../include/map_widget.h"
#include "../include/new_tile.h"
#include <string>
#include <iostream>
#include <fstream>
#include <QtWidgets>
#include "map.h"
#include "map_translator.h"
#include <yaml-cpp/yaml.h>

#define BLUE_WALL "../../editor/resources/blue-wall.jpg"
#define GREY_WALL "../../editor/resources/grey-wall.jpg"
#define WOOD_WALL "../../editor/resources/wood-wall.jpg"
#define DOOR "../../editor/resources/door.jpg"
#define KEY_DOOR "../../editor/resources/keydoor.jpg"

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
    Map map = MapTranslator::yamlToMap(YAML::LoadFile(fileName.toStdString()),450);//cheqs
    mapWidget = new MapWidget(mapWidget->tileSize() * map.getColSize(), mapWidget->tileSize() * map.getRowSize());
    mapTilesList = new MapTilesList(mapWidget->tileSize(), this);

    QFrame *frame = new QFrame;
    QHBoxLayout *mapLayout = new QHBoxLayout(frame);
    mapLayout->addWidget(mapTilesList);
    QScrollArea *area = new QScrollArea;
    area->setMinimumSize(QSize(450, 450));
    area->setWidgetResizable(true);
    area->setWidget(mapWidget);
    mapLayout->addWidget(area);

    setCentralWidget(frame);

    initTiles();

    for (int i = 0; i < map.getColSize(); ++i) {
        for (int j = 0; j < map.getRowSize(); ++j) {
            Type type = map(i, j);
            if ("wall" == type.getName()) {
                QPoint point(i * mapWidget->tileSize(), j * mapWidget->tileSize());
                QPixmap newImage;
                newImage.load(QStringLiteral(BLUE_WALL));
                QPixmap pixmap = newImage.scaled(mapWidget->tileSize(), mapWidget->tileSize());
                mapWidget->addTile(point, pixmap, map(i, j).getType());
            } else if ("wall-2" == type.getName()) {
                QPoint point(i * mapWidget->tileSize(), j * mapWidget->tileSize());
                QPixmap newImage;
                newImage.load(QStringLiteral(WOOD_WALL));
                QPixmap pixmap = newImage.scaled(mapWidget->tileSize(), mapWidget->tileSize());
                mapWidget->addTile(point, pixmap, map(i, j).getType());
            } else if ("wall-3" == type.getName()) {
                QPoint point(i * mapWidget->tileSize(), j * mapWidget->tileSize());
                QPixmap newImage;
                newImage.load(QStringLiteral(GREY_WALL));
                QPixmap pixmap = newImage.scaled(mapWidget->tileSize(), mapWidget->tileSize());
                mapWidget->addTile(point, pixmap, map(i, j).getType());
            } else if ("door" == type.getName()) {
                QPoint point(i * mapWidget->tileSize(), j * mapWidget->tileSize());
                QPixmap newImage;
                newImage.load(QStringLiteral(DOOR));
                QPixmap pixmap = newImage.scaled(mapWidget->tileSize(), mapWidget->tileSize());
                mapWidget->addTile(point, pixmap, map(i, j).getType());
            } else if ("fakeDoor" == type.getName()) {
                QPoint point(i * mapWidget->tileSize(), j * mapWidget->tileSize());
                QPixmap newImage;
                newImage.load(QStringLiteral(GREY_WALL));
                QPixmap pixmap = newImage.scaled(mapWidget->tileSize(), mapWidget->tileSize());
                mapWidget->addTile(point, pixmap, map(i, j).getType());
            } else if ("keyDoor" == type.getName()) {
                QPoint point(i * mapWidget->tileSize(), j * mapWidget->tileSize());
                QPixmap newImage;
                newImage.load(QStringLiteral(KEY_DOOR));
                QPixmap pixmap = newImage.scaled(mapWidget->tileSize(), mapWidget->tileSize());
                mapWidget->addTile(point, pixmap, map(i, j).getType());
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
        QScrollArea *area = new QScrollArea;
        area->setMinimumSize(QSize(450, 450));
        area->setWidgetResizable(true);
        area->setWidget(mapWidget);
        mapLayout->addWidget(area);

        setCentralWidget(frame);

        initTiles();
    }
}

void MainWindow::initTiles() {
    addTile(QStringLiteral("blue wall"), QStringLiteral("../../editor/resources/blue-wall.jpg"),
            ObjetosJuego::obtenerTipoPorNombre("wall"));
    addTile(QStringLiteral("grey wall"), QStringLiteral("../../editor/resources/grey-wall.jpg"),
            ObjetosJuego::obtenerTipoPorNombre("wall-2"));
    addTile(QStringLiteral("fake wall"), QStringLiteral("../../editor/resources/grey-wall.jpg"),
            ObjetosJuego::obtenerTipoPorNombre("fakeDoor"));
    addTile(QStringLiteral("wood wall"), QStringLiteral("../../editor/resources/wood-wall.jpg"),
            ObjetosJuego::obtenerTipoPorNombre("wall-3"));
    addTile(QStringLiteral("door"), QStringLiteral("../../editor/resources/door.jpg"),
            ObjetosJuego::obtenerTipoPorNombre("door"));
    addTile(QStringLiteral("key door"), QStringLiteral("../../editor/resources/keydoor.jpg"),
            ObjetosJuego::obtenerTipoPorNombre("keydoor"));
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

void MainWindow::addTile(const QString &name, const QString &path, Type type) {
    QPixmap newImage;
    if (!newImage.load(path)) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No se pudo cargar el icono"),
                             QMessageBox::Close);
        return;
    }

    int tileSize = mapWidget->tileSize();
    QPixmap scaledImg = newImage.scaled(tileSize, tileSize);
    mapTilesList->addTile(name, scaledImg, type);
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

QWizardPage *createIntroPage() {
    QWizardPage *page = new QWizardPage;
    page->setTitle("Crear item");

    QLabel *nameLabel = new QLabel("Tipo:");
    QLineEdit *nameLineEdit = new QLineEdit;

    QLabel *emailLabel = new QLabel("Imagen:");
    QLineEdit *emailLineEdit = new QLineEdit;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(emailLabel, 1, 0);
    layout->addWidget(emailLineEdit, 1, 1);
    page->setLayout(layout);

    return page;
}

void MainWindow::addTile() {
    NewTile window(this);
    window.exec();
}

void MainWindow::deleteTile() {
    QAction *pAction = qobject_cast<QAction *>(sender());
    QPoint point = pAction->data().toPoint();
    QListWidgetItem *it = this->mapTilesList->itemAt(point);
    this->mapTilesList->takeItem(this->mapTilesList->row(it));
}

void MainWindow::showContextMenu(const QPoint &pos) {
    QPoint globalPos = mapTilesList->mapToGlobal(pos);
    QMenu myMenu;
    QAction *action = new QAction(tr("Add new item"), this);
    action->setData(pos);
    connect(action, SIGNAL(triggered()), this, SLOT(addTile()));

    myMenu.addAction(action);
    QListWidgetItem *it = this->mapTilesList->itemAt(pos);
    if (it != nullptr) {
        QAction *action = new QAction(tr("Delete ") + it->text(), this);
        action->setData(pos);
        connect(action, SIGNAL(triggered()), this, SLOT(deleteTile()));

        myMenu.addAction(action);
        //  myMenu.addAction("Delete " + it->text(), this, SLOT(deleteTile()));
    }
    myMenu.exec(globalPos);
}

void MainWindow::setupWidgets() {
    mapWidget = new MapWidget(400, 400);
    mapTilesList = new MapTilesList(mapWidget->tileSize(), this);

    mapTilesList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mapTilesList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    QObject::connect(mapTilesList, SIGNAL(tileDoubleClicked(int, QPixmap)), mapWidget,
                     SLOT(onTileDoubleClicked(int, QPixmap)));
    QFrame *frame = new QFrame;
    QHBoxLayout *mapLayout = new QHBoxLayout(frame);
    QScrollArea *area = new QScrollArea;
    area->setMinimumSize(QSize(450, 450));
    area->setWidgetResizable(true);
    area->setWidget(mapWidget);
    mapLayout->addWidget(mapTilesList);
    mapLayout->addWidget(area);

    setCentralWidget(frame);
}

MainWindow::~MainWindow() {

}
