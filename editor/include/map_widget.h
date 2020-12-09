#ifndef MAP_WIDGET_H
#define MAP_WIDGET_H

#include <QPoint>
#include <QPixmap>
#include <QVector>
#include <QWidget>
#include "map.h"

class QDragEnterEvent;

class QDropEvent;

class QMouseEvent;

class MapWidget : public QWidget {
Q_OBJECT

public:
    explicit MapWidget(int height, int width, QWidget *parent = nullptr);

    void clear();

    int tileSize() const;

    Map toMap();

    ~MapWidget();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;

    void dragLeaveEvent(QDragLeaveEvent *event) override;

    void dragMoveEvent(QDragMoveEvent *event) override;

    void dropEvent(QDropEvent *event) override;

    void paintEvent(QPaintEvent *event) override;


private:
    struct Tile {
        QPixmap pixmap;
        QRect rect;
        int type = 0;
    };

    int findTile(const QRect &tileRect) const;

    const QRect targetSquare(const QPoint &position) const;

    QVector<Tile> tiles;
    QRect highlightedRect;
};

#endif // MAP_WIDGET_H
