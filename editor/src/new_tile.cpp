#include "../include/new_tile.h"

#include <QtWidgets>
#include "objetosJuego.h"
#include <string>

NewTile::NewTile(QWidget *parent)
        : QDialog(parent) {
    setWindowTitle(tr("Create item"));
    QPushButton *browseButton = new QPushButton(tr("&Browse..."), this);
    connect(browseButton, &QAbstractButton::clicked, this, &NewTile::browse);

    createButton = new QPushButton(tr("&Create"), this);
    connect(createButton, &QAbstractButton::clicked, this, &NewTile::create);

    textComboBox = createComboBox();
    directoryLine = new QLineEdit;

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(new QLabel(tr("Type:")), 1, 0);
    mainLayout->addWidget(textComboBox, 1, 1, 1, 2);
    mainLayout->addWidget(new QLabel(tr("Image:")), 2, 0);
    mainLayout->addWidget(directoryLine, 2, 1);
    mainLayout->addWidget(browseButton, 2, 2);
    mainLayout->addWidget(createButton, 4, 2);

    connect(new QShortcut(QKeySequence::Quit, this), &QShortcut::activated,
            qApp, &QApplication::quit);
}

void NewTile::browse() {
    QString directory = QFileDialog::getOpenFileName(this,
                                                               tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!directory.isEmpty()) {
        directoryLine->setText(directory);
    }
}

void NewTile::create() {
    QString text = textComboBox->currentText();
    QFileInfo file(directoryLine->text());
    MainWindow* pMainWindow = qobject_cast<MainWindow*>(parent());
    if (pMainWindow) {
        std::string utf8_text = text.toUtf8().constData();
        pMainWindow->addTile(file.baseName(), file.filePath(), ObjetosJuego::obtenerTipoPorNombre(utf8_text));
    }

}

QComboBox *NewTile::createComboBox(const QString &text) {
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    for (Type t : ObjetosJuego::obtenerObjetos()) {
        QString s = QString::fromStdString(t.getName());
        comboBox->addItem(s);
    }
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}
