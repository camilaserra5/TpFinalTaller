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

    void addTile(const QString &path, Type type);

    ~MainWindow();

public slots:

    void openMap();

    void saveMap();

private:
    void setupMenus();

    void setupWidgets();

    MapTilesList *mapTilesList;
    MapWidget *mapWidget;
};

#endif // MAINWINDOW_H
