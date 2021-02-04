#include "../include/map_tiles_list.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <iostream>
#include <include/map_widget.h>

MapTilesList::MapTilesList(int tileSize, QWidget *parent)
        : QListWidget(parent), tileSize(tileSize) {
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(tileSize, tileSize));
    setSpacing(10);
    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem * )), this, SLOT(itemDoubleClicked(QListWidgetItem * )));
}

void MapTilesList::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasFormat(MapTilesList::tileMimeType())) {
        event->setDropAction(Qt::CopyAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void MapTilesList::itemDoubleClicked(QListWidgetItem *item) {
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
    int type = item->data(Qt::UserRole + 1).toInt();
    emit tileDoubleClicked(type, pixmap);
}

void MapTilesList::addTile(const QString &name, const QPixmap &pixmap, Type type) {
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole + 1, static_cast<int >(type));
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    pieceItem->setText(name);
}

void MapTilesList::startDrag(Qt::DropActions /*supportedActions*/) {
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
    int type = item->data(Qt::UserRole + 1).toInt();

    dataStream << pixmap << type;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(MapTilesList::tileMimeType(), itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));
    drag->setPixmap(pixmap);

    if (drag->exec(Qt::CopyAction) == Qt::CopyAction)
        row(item);
}


MapTilesList::~MapTilesList() {

}
