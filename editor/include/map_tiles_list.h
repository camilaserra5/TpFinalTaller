#ifndef MAP_TILES_LIST_H
#define MAP_TILES_LIST_H

#include <QListWidget>
#include "map.h"

class MapTilesList : public QListWidget {
    Q_OBJECT

public:
    explicit MapTilesList(int pieceSize, QWidget *parent = nullptr);

    void addTile(const QString& name, const QPixmap &pixmap, const Type type);

    static QString tileMimeType() { return QStringLiteral("image/x-tile"); }

    ~MapTilesList();

    signals:

            void tileDoubleClicked(int, QPixmap);

public
    slots:

            void itemDoubleClicked(QListWidgetItem * item);

protected:


    void dragMoveEvent(QDragMoveEvent *event) override;

    void startDrag(Qt::DropActions supportedActions) override;

    int tileSize;
};

#endif // MAP_TILES_LIST_H
