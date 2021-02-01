#ifndef MAP_H
#define MAP_H

#include <vector>
#include "contenedorDeElementos.h"
#include "items/item.h"
#include "objetosJuego.h"
#include "iserializable.h"
#include <iostream>
#include "puerta.h"
// faltaria agregar una posicion para los jugadores
// tambien el tema de los itemas(comida, sangre, todas las armas);

class Map : public ISerializable {
public:
//largo preconcatenado
    Map(unsigned rowSize, unsigned colSize);

    unsigned getRowSize() const;

    unsigned getColSize() const;

    void setValue(const unsigned rowNumber, const unsigned colNumber, Type value);

    Type &operator()(const unsigned rowNumber, const unsigned colNumber);

    void crearElementoPosicionable(const unsigned rowNumber, const unsigned colSize, Type value);

    Item *buscarElemento(int &posx, int &posy);

    ContenedorDeElementos &obtenerContenedor() {
        return this->contenedorDeElementos;
    };

    ~Map();

    void agregarElemento(Item *item);

    std::vector<char> serializar() override {
        std::vector<char> informacion;
        informacion.push_back(this->rowSize);
        informacion.push_back(this->colSize);
        for (unsigned i = 0; i < rowSize; i++) {
            for (unsigned j = 0; j < colSize; j++) {
                informacion.push_back(static_cast<int>(map[i][j]));
            }
        }
        std::vector<char> contenedorSerializado = this->contenedorDeElementos.serializar();
        informacion.insert(informacion.end(), contenedorSerializado.begin(), contenedorSerializado.end());
        return informacion;
    }

    void deserializar(std::vector<char> &serializado) override {
        this->rowSize = (int) serializado[0];
        this->colSize = (int) serializado[1];
        int idx = 2;
        for (unsigned i = 0; i < rowSize; i++) {
            for (unsigned j = 0; j < colSize; j++) {
                setValue(i, j, static_cast<Type>(serializado[idx++]));
            }
        }
        std::vector<char> contenedorDeElementosSerializado(serializado.begin() + idx,
                                                           serializado.end());
        this->contenedorDeElementos.deserializar(contenedorDeElementosSerializado);
    }
    std::vector<Item*>& obtenerItems(){
        return this->contenedorDeElementos.obtenerItems();
    }

    Puerta& puertaMasCercana(Posicion& posicionJugador,double& distancia);

    bool hayPuertas();

private:
    unsigned rowSize;
    unsigned colSize;
    ContenedorDeElementos contenedorDeElementos;
    std::vector<std::vector<Type>> map;
};

#endif //MAP_H
