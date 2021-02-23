#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include "map.h"
#include <config.h>

#define ARCHIVO_DE_CONFIGURACION EDITOR_DIR "config.yaml"

class MapTilesList;

class MapWidget;

class QListWidgetItem;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(std::string configFile, QWidget *parent = nullptr);

    void initTiles();

    void addTile(const QString &name, const QString &path, Type type);
    void addItemTile(const QString &name, const QString &path, Type type, int x, int y);
    void addItemTileZoomed(const QString &name, const QString &path, Type type, int x, int y);


    ~MainWindow();

public
    slots:

            void openMap();

    void addTile();

    void deleteTile();

    void showContextMenu(const QPoint &pos);

    void newMap();

    void saveMap();

private:


    void setupMenus();

    void setupWidgets();

    MapTilesList *mapTilesList;
    MapWidget *mapWidget;
    std::string configFile = ARCHIVO_DE_CONFIGURACION;
    ConfiguracionPartida configuracionPartida;
    std::map<std::string, QPixmap> images;
};

#endif // MAINWINDOW_H
