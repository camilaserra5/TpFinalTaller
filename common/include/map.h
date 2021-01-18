#ifndef MAP_H
#define MAP_H

#include <vector>
#include "contenedorDeElementos.h"
#include "items/item.h"

// faltaria agregar una posicion para los jugadores
// tambien el tema de los itemas(comida, sangre, todas las armas);
enum class Type {
    empty = 0, door = 1, wall = 2, fakeDoor = 3, keyDoor = 4, comida = 5,
    kitsMedicos = 6, sangre = 7, balas = 8, lanzaCohetes = 9, ametralladora = 10,
    canionDeCadena = 11, llave = 12, tesoro = 13
};

class Map {
public:

    Map(unsigned rowSize, unsigned colSize);

    unsigned getRowSize() const;

    unsigned getColSize() const;

    void setValue(const unsigned rowNumber, const unsigned colNumber, Type value);

    Type &operator()(const unsigned rowNumber, const unsigned colNumber);

    void crearElementoPosicionable(const unsigned rowNumber, const unsigned colSize, Type value);

    Item *buscarElemento(int &posx, int &posy);

    ~Map();

private:
    unsigned rowSize;
    unsigned colSize;
    ContenedorDeElementos contenedorDeElementos;
    std::vector<std::vector<Type>> map;
};

#endif //MAP_H
