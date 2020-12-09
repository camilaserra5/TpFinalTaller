#include <string>
#include <iostream>
#include <fstream>

#include "../include/mainwindow.h"
#include "map.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    /** ejemplo para pasar de yaml a mapa y de mapa a yaml
     * crear archivo config.yaml en TpFinalTaller/build/src con datos (o copiar el que está acá)
     */
    /* Map m = MapTranslator::yamlToMap(YAML::LoadFile("../src/config.yaml"));
     std::cout << m.getColSize() << std::endl;
     std::cout << m.getRowSize() << std::endl;
     for (std::size_t i = 0; i < m.getRowSize(); i++) {
         for (std::size_t j = 0; j < m.getColSize(); j++) {
             m.setValue(i, j, m(i, j));
         }
     }
     YAML::Node node = MapTranslator::mapToYaml(m);
     std::ofstream file("confignew.yaml");
     file << node;
     file.close();*/
    /** fin ejemplo **/

    QApplication app(argc, argv);
    MainWindow window;
    window.addTile(QStringLiteral("../../editor/resources/wall1.jpg"), Type::wall);
    window.addTile(QStringLiteral("../../editor/resources/wall2.jpg"), Type::door);
    window.addTile(QStringLiteral("../../editor/resources/wall3.jpg"), Type::fakeDoor);
    window.show();
    return app.exec();
}
