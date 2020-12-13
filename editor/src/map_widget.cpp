#include "../include/map_widget.h"
#include "../include/map_tiles_list.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <iostream>

MapWidget::MapWidget(int height, int width, QWidget *parent)
        : QWidget(parent) {
    setAcceptDrops(true);
    setMinimumSize(height, width);
    setMaximumSize(height, width);
}

void MapWidget::clear() {
    tiles.clear();
    highlightedRect = QRect();
    update();
}

void MapWidget::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat(MapTilesList::tileMimeType()))
        event->accept();
    else
        event->ignore();
}

void MapWidget::dragLeaveEvent(QDragLeaveEvent *event) {
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    event->accept();
}

void MapWidget::dragMoveEvent(QDragMoveEvent *event) {
    QRect updateRect = highlightedRect.united(targetSquare(event->pos()));

    if (event->mimeData()->hasFormat(MapTilesList::tileMimeType())
        && findTile(targetSquare(event->pos())) == -1) {

        highlightedRect = targetSquare(event->pos());
        event->setDropAction(Qt::CopyAction);
        event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }

    update(updateRect);
}

void MapWidget::addTile(const QPoint &position, const QPixmap pixmap, const int type) {
    Tile tile;
    tile.rect = targetSquare(position);
    tile.pixmap = pixmap;
    tile.type = type;
    tiles.append(tile);
    update(tile.rect);
}

void MapWidget::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat(MapTilesList::tileMimeType())
        && findTile(targetSquare(event->pos())) == -1) {

        QByteArray tileData = event->mimeData()->data(MapTilesList::tileMimeType());
        QDataStream dataStream(&tileData, QIODevice::ReadOnly);
        Tile tile;
        tile.rect = targetSquare(event->pos());

        dataStream >> tile.pixmap >> tile.type;

        tiles.append(tile);

        highlightedRect = QRect();
        update(tile.rect);

        event->setDropAction(Qt::CopyAction);
        event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }
}

int MapWidget::findTile(const QRect &tileRect) const {
    for (int i = 0, size = tiles.size(); i < size; ++i) {
        if (tiles.at(i).rect == tileRect)
            return i;
    }
    return -1;
}

void MapWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::white);

    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }

    for (const Tile &tile : tiles)
        painter.drawPixmap(tile.rect, tile.pixmap);
}

const QRect MapWidget::targetSquare(const QPoint &position) const {
    return QRect(position / tileSize() * tileSize(),
                 QSize(tileSize(), tileSize()));
}

Map MapWidget::toMap() {
    Map map(10, 10);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            QPoint point(i * tileSize(), j * tileSize());
            for (int k = 0, size = tiles.size(); k < size; ++k) {
                map.setValue(i, j, Type::empty);
                if (tiles.at(k).rect == targetSquare(point)) {
                    map.setValue(i, j, static_cast<Type>(tiles.at(k).type));
                }
            }
        }
    }
    return map;
}

int MapWidget::tileSize() const {
    return 40;
}

MapWidget::~MapWidget() {

}