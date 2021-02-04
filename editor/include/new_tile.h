#ifndef CLIENT_NEW_TILE_H
#define CLIENT_NEW_TILE_H

#include <QWidget>
#include <QDir>
#include "mainwindow.h"
#include <QDialog>
#include <QDir>

class QComboBox;

class QLineEdit;

class QLabel;

class QPushButton;

class QTableWidget;

class QTableWidgetItem;

class NewTile : public QDialog {
    Q_OBJECT

public:
    NewTile(QWidget
            *
            parent = 0
    );

private
    slots:
            void browse();

    void create();

private:
    QComboBox *createComboBox(const QString &text = QString());
    QComboBox *textComboBox;
    QLineEdit *directoryLine;
    QPushButton *createButton;
};

#endif //CLIENT_NEW_TILE_H
