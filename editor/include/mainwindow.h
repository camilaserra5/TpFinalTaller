#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include "map.h"

class MapTilesList;

class MapWidget;

class QListWidgetItem;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void initTiles();
    void addTile(const QString &name, const QString &path, Type type);
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


};

#endif // MAINWINDOW_H
