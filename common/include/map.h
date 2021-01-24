#ifndef MAP_H
#define MAP_H

#include <vector>
#include "contenedorDeElementos.h"
#include "items/item.h"
#include "objetosJuego.h"

// faltaria agregar una posicion para los jugadores
// tambien el tema de los itemas(comida, sangre, todas las armas);

class Map {
public:

    Map(unsigned rowSize, unsigned colSize);

    unsigned getRowSize() const;

    unsigned getColSize() const;

    void setValue(const unsigned rowNumber, const unsigned colNumber, Type value);

    Type &operator()(const unsigned rowNumber, const unsigned colNumber);

    void crearElementoPosicionable(const unsigned rowNumber, const unsigned colSize, Type value);

    Item *buscarElemento(int &posx, int &posy);

    ContenedorDeElementos& obtenerContenedor(){
        return this->contenedorDeElementos;
    };

    ~Map();

private:
    unsigned rowSize;
    unsigned colSize;
    ContenedorDeElementos contenedorDeElementos;
    std::vector<std::vector<Type>> map;
};

#endif //MAP_H
