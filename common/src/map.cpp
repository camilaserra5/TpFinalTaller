#include "../include/map.h"
#include <iostream>
#include "items/item.h"
#include "armas/arma.h"
#include "items/comida.h"
#include "items/balas.h"
#include "items/sangre.h"
#include "items/kitsMedicos.h"
#include "items/noItem.h"
#include "items/llave.h"
#include "items/tesoro.h"
#include "armas/canionDeCadena.h"
#include "armas/ametralladora.h"
#include "armas/lanzacohetes.h"

#define TAM_CELDA 50
Map::Map(unsigned rowSize, unsigned colSize) : contenedorDeElementos() {
    if (rowSize < 1 || colSize < 1) {
        throw std::runtime_error("Invalid map");
    }

    this->rowSize = rowSize;
    this->colSize = colSize;
    map.resize(rowSize);
    for (unsigned i = 0; i < map.size(); i++) {
        map[i].resize(colSize, Type::empty);
    }
}

unsigned Map::getRowSize() const {
    return this->rowSize;
}

unsigned Map::getColSize() const {
    return this->colSize;
}

// pre condicion: va a ver un item por celda por facilidad, ya que sino se pisan;
void Map::crearElementoPosicionable(const unsigned rowNumber, const unsigned colNumber,
                                    Type value) {
    srand(time(NULL));
    int posElementox = 0;
    int posElementoy = 0;
    if (rowNumber == 0) {
        posElementox = (rowNumber * TAM_CELDA + rand() % ((1 + rowNumber) * TAM_CELDA));
    } else if (colNumber == 0) {
        int posElementoy = (colNumber * TAM_CELDA + rand() % ((1 + rowNumber) * TAM_CELDA));
    } else {
        posElementox = (rowNumber * TAM_CELDA + rand() % ((1 + rowNumber) * TAM_CELDA - rowNumber * TAM_CELDA));
        posElementoy = (colNumber * TAM_CELDA + rand() % ((1 + rowNumber) * TAM_CELDA - colNumber * TAM_CELDA));
    }
    Posicion posicion = Posicion(posElementox, posElementoy, 0);
    if (value == Type::comida) {
        //  Comida comida = new Comida(posicion);
        Posicion prueba = Posicion(4, 6, 0);
        std::cout << "agrego comuda\n";
        this->contenedorDeElementos.agregarElemento(new Comida(prueba));
    } else if (value == Type::sangre) {
        //Sangre sangre = new Sangre(posicion);
        this->contenedorDeElementos.agregarElemento(new Sangre(posicion));
    } else if (value == Type::kitsMedicos) {
        this->contenedorDeElementos.agregarElemento(new KitsMedicos(posicion));
    } else if (value == Type::balas) {
        this->contenedorDeElementos.agregarElemento(new Balas(posicion, BALAS));
    } else if (value == Type::ametralladora) {
        this->contenedorDeElementos.agregarElemento(new Ametralladora(posicion));
    } else if (value == Type::canionDeCadena) {
        this->contenedorDeElementos.agregarElemento(new CanionDeCadena(posicion));
    } else if (value == Type::lanzaCohetes) {
        this->contenedorDeElementos.agregarElemento(new LanzaCohetes(posicion));
    } else if (value == Type::tesoro) {
        std::string tesoro("copa");
        int puntos = 50;
        this->contenedorDeElementos.agregarElemento(new Tesoro(tesoro, puntos, posicion));
    } else if (value == Type::llave) {
        this->contenedorDeElementos.agregarElemento(new Llave(posicion));
    } else {
        std::cout << "agrego no item\n";
        this->contenedorDeElementos.agregarElemento(new NoItem(posicion));
    }

}

void Map::agregarElemento(Item *item) {
    this->agregarElemento(item);
}

Item *Map::buscarElemento(int &posx, int &posy) {
    return this->contenedorDeElementos.buscarElemento(posx, posy);
}

void Map::setValue(const unsigned rowNumber, const unsigned colNumber, Type value) {
    this->map[rowNumber][colNumber] = value;
    this->crearElementoPosicionable(rowNumber, colNumber, value);
}

Type &Map::operator()(const unsigned rowNumber, const unsigned colNumber) {
    return this->map[rowNumber][colNumber];
}

Map::~Map() {

}

bool Map::hayPuertas(){
    return this->contenedorDeElementos.hayPuertas();
}

Puerta& Map::puertaMasCercana(Posicion& posicionJugador,double& distancia){
  return this->contenedorDeElementos.puertaMasCercana(posicionJugador,distancia);

}
