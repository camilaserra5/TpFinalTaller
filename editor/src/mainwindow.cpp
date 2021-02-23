#include "../include/mainwindow.h"
#include "../include/map_tiles_list.h"
#include "../include/map_widget.h"
#include "../include/new_tile.h"
#include <QtWidgets>
#include "map_translator.h"
#include <config.h>
#include "parser.h"

#define SPRITE_WIDTH 64.8
#define SPRITE_HEIGHT 65
#define SPRITE_OBJETOS IMGS_DIR OBJECTS_IMG
#define BLUE_WALL IMGS_DIR BLUE_WALL_IMG
#define GREY_WALL IMGS_DIR GREY_WALL_IMG
#define WOOD_WALL IMGS_DIR WOOD_WALL_IMG
#define DOOR IMGS_DIR DOOR_IMG
#define KEY_DOOR IMGS_DIR KEYDOOR_IMG

MainWindow::MainWindow(std::string configFile, QWidget *parent) : QMainWindow(parent) {
    if (!configFile.empty()) {
        this->configFile = configFile;
    }
    Parser parser(this->configFile);
    this->configuracionPartida = parser.obtenerParametrosDeConfiguracion();
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
    Map map = MapTranslator::yamlToMap(YAML::LoadFile(fileName.toStdString()), 450, configuracionPartida);//cheqs
    mapWidget = new MapWidget(mapWidget->tileSize() * map.getColSize(), mapWidget->tileSize() * map.getRowSize(),
                              this->configuracionPartida);
    mapTilesList = new MapTilesList(mapWidget->tileSize(), this);
    QObject::connect(mapTilesList, SIGNAL(tileDoubleClicked(int, QPixmap)), mapWidget,
                     SLOT(onTileDoubleClicked(int, QPixmap)));
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
            if (images.count(type.getName()) > 0) {
                QPoint point(i * mapWidget->tileSize(), j * mapWidget->tileSize());
                mapWidget->addTile(point, images.at(type.getName()), map(i, j).getType());
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
                                  mapWidget->tileSize() * heightSpinbox->value(),
                                  this->configuracionPartida);
        mapTilesList = new MapTilesList(mapWidget->tileSize(), this);
        QObject::connect(mapTilesList, SIGNAL(tileDoubleClicked(int, QPixmap)), mapWidget,
                         SLOT(onTileDoubleClicked(int, QPixmap)));
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
    addTile(QStringLiteral("blue wall"), QStringLiteral(BLUE_WALL), ObjetosJuego::obtenerTipoPorNombre("wall"));
    addTile(QStringLiteral("grey wall"), QStringLiteral(GREY_WALL), ObjetosJuego::obtenerTipoPorNombre("wall-2"));
    addTile(QStringLiteral("fake wall"), QStringLiteral(GREY_WALL), ObjetosJuego::obtenerTipoPorNombre("fakeDoor"));
    addTile(QStringLiteral("wood wall"), QStringLiteral(WOOD_WALL), ObjetosJuego::obtenerTipoPorNombre("wall-3"));
    addTile(QStringLiteral("door"), QStringLiteral(DOOR), ObjetosJuego::obtenerTipoPorNombre("door"));
    addTile(QStringLiteral("key door"), QStringLiteral(KEY_DOOR), ObjetosJuego::obtenerTipoPorNombre("keydoor"));
    addItemTileZoomed(QStringLiteral("comida"), QStringLiteral(SPRITE_OBJETOS),
                      ObjetosJuego::obtenerTipoPorNombre("comida"), 1, 5);
    addItemTileZoomed(QStringLiteral("kits medicos"), QStringLiteral(SPRITE_OBJETOS),
                      ObjetosJuego::obtenerTipoPorNombre("kitsMedicos"), 2, 5);
    addItemTileZoomed(QStringLiteral("llave"), QStringLiteral(SPRITE_OBJETOS),
                      ObjetosJuego::obtenerTipoPorNombre("llave"), 2, 4);
    addItemTileZoomed(QStringLiteral("balas"), QStringLiteral(SPRITE_OBJETOS),
                      ObjetosJuego::obtenerTipoPorNombre("balas"), 3, 5);
    addItemTileZoomed(QStringLiteral("sangre"), QStringLiteral(SPRITE_OBJETOS),
                      ObjetosJuego::obtenerTipoPorNombre("sangre"), 0, 8);
    addItemTileZoomed(QStringLiteral("cruz"), QStringLiteral(SPRITE_OBJETOS),
                      ObjetosJuego::obtenerTipoPorNombre("cruz"), 1, 6);
    addItemTileZoomed(QStringLiteral("copa"), QStringLiteral(SPRITE_OBJETOS),
                      ObjetosJuego::obtenerTipoPorNombre("copa"), 2, 6);
    addItemTileZoomed(QStringLiteral("cofre"), QStringLiteral(SPRITE_OBJETOS),
                      ObjetosJuego::obtenerTipoPorNombre("cofre"), 3, 6);
    addItemTileZoomed(QStringLiteral("corona"), QStringLiteral(SPRITE_OBJETOS),
                      ObjetosJuego::obtenerTipoPorNombre("corona"), 4, 6);
    addItemTile(QStringLiteral("ametralladora"), QStringLiteral(SPRITE_OBJETOS),
                ObjetosJuego::obtenerTipoPorNombre("ametralladora"), 4, 5);
    addItemTile(QStringLiteral("lanza cohetes"), QStringLiteral(SPRITE_OBJETOS),
                ObjetosJuego::obtenerTipoPorNombre("lanzaCohetes"), 0, 6);
    addItemTile(QStringLiteral("barril"), QStringLiteral(SPRITE_OBJETOS), ObjetosJuego::obtenerTipoPorNombre("barril"),
                2, 7);
    addItemTileZoomed(QStringLiteral("agua"), QStringLiteral(SPRITE_OBJETOS),
                      ObjetosJuego::obtenerTipoPorNombre("agua"), 2, 0);
    addItemTile(QStringLiteral("tanque"), QStringLiteral(SPRITE_OBJETOS), ObjetosJuego::obtenerTipoPorNombre("tanque"),
                3, 0);
    addItemTile(QStringLiteral("mesa"), QStringLiteral(SPRITE_OBJETOS), ObjetosJuego::obtenerTipoPorNombre("mesa"), 4,
                0);
    addItemTile(QStringLiteral("lampara"), QStringLiteral(SPRITE_OBJETOS),
                ObjetosJuego::obtenerTipoPorNombre("lampara"), 0, 1);
    addItemTile(QStringLiteral("muerto colgante"), QStringLiteral(SPRITE_OBJETOS),
                ObjetosJuego::obtenerTipoPorNombre("muertoColgante"), 2, 1);
    addItemTile(QStringLiteral("planta"), QStringLiteral(SPRITE_OBJETOS), ObjetosJuego::obtenerTipoPorNombre("planta"),
                0, 2);
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
    images.insert(std::make_pair(type.getName(), scaledImg));
}


void MainWindow::addItemTile(const QString &name, const QString &path, Type type, int x, int y) {
    QPixmap newImage;
    if (!newImage.load(path)) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No se pudo cargar el icono"),
                             QMessageBox::Close);
        return;
    }

    int tileSize = mapWidget->tileSize();
    QRect rect(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT);
    QPixmap cropped = newImage.copy(rect);
    QPixmap scaledImg = cropped.scaled(tileSize, tileSize);
    mapTilesList->addTile(name, scaledImg, type);

    images.insert(std::make_pair(type.getName(), scaledImg));
}


void MainWindow::addItemTileZoomed(const QString &name, const QString &path, Type type, int x, int y) {
    QPixmap newImage;
    if (!newImage.load(path)) {
        QMessageBox::warning(this, tr("Error"),
                             tr("No se pudo cargar el icono"),
                             QMessageBox::Close);
        return;
    }

    int tileSize = mapWidget->tileSize();
    QRect rect((x + 0.25) * SPRITE_WIDTH, (y + 0.5) * SPRITE_HEIGHT, SPRITE_WIDTH / 2, SPRITE_HEIGHT / 2);
    QPixmap cropped = newImage.copy(rect);
    QPixmap scaledImg = cropped.scaled(tileSize, tileSize);
    mapTilesList->addTile(name, scaledImg, type);
    images.insert(std::make_pair(type.getName(), scaledImg));
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
    mapWidget = new MapWidget(400, 400, this->configuracionPartida);
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
