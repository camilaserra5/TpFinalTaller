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

void MapWidget::onTileDoubleClicked(int type, QPixmap pixmap) {
    Tile tile;
    tile.type = type;
    tile.pixmap = pixmap;
        this->selectedTile = tile;
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
    if (event->mimeData()->hasFormat(MapTilesList::tileMimeType())) {
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
    if (event->mimeData()->hasFormat(MapTilesList::tileMimeType())) {
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
    Map map(this->height() / this->tileSize(), this->width() / this->tileSize());
    for (int i = 0; i < map.getColSize(); ++i) {
        for (int j = 0; j < map.getRowSize(); ++j) {
            QPoint point(i * tileSize(), j * tileSize());
            for (int k = 0, size = tiles.size(); k < size; ++k) {
                map.setValue(i, j, ObjetosJuego::obtenerTipoPorNombre("empty"));
                if (tiles.at(k).rect == targetSquare(point)) {
                    map.setValue(i, j, ObjetosJuego::obtenerTipoPorId(tiles.at(k).type));
                }
            }
        }
    }
    return map;
}

void MapWidget::mousePressEvent(QMouseEvent *event) {
    startPoint = event->pos();
    pressed = true;
    update();
}

void MapWidget::mouseMoveEvent(QMouseEvent *event) {
    if (pressed) {
        QRect updateRect = highlightedRect.united(targetSquare(event->pos()));
        highlightedRect = targetSquare(event->pos());
        Tile tile;
        tile.rect = targetSquare(event->pos());
        tile.pixmap = this->selectedTile.pixmap;
        tile.type = this->selectedTile.type;
        tiles.append(tile);
        highlightedRect = QRect();
        update(tile.rect);
        event->accept();
        update(updateRect);
    }
}

void MapWidget::mouseReleaseEvent(QMouseEvent *event) {
    pressed = false;
    Tile tile;
    tile.rect = targetSquare(event->pos());
    tile.pixmap = this->selectedTile.pixmap;
    tile.type = this->selectedTile.type;
    tiles.append(tile);
    highlightedRect = QRect();
    update(tile.rect);
    event->accept();

}

int MapWidget::tileSize() const {
    return 40;
}

MapWidget::~MapWidget() {

}