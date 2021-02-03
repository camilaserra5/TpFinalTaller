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
#define PUNTOS_CRUZ 10
#define PUNTOS_COPA 50
#define PUNTOS_COFRE 100
#define PUNTOS_CORONA 200

void Map::agregarArma(Posicion& posicion,Arma* arma){
  Type tipo = arma->getTipo();
  if (tipo == Type::ametralladora){
    Item* ametralladora = new Ametralladora(posicion,arma->getId());
    this->contenedorDeElementos.agregarElemento(ametralladora);
  }else if (tipo == Type::canionDeCadena){
    Item* canion = new CanionDeCadena(posicion,arma->getId());
    this->contenedorDeElementos.agregarElemento(canion);
  }else if (tipo == Type::lanzaCohetes){
    Item* lanzaCohetes = new LanzaCohetes(posicion,arma->getId());
    this->contenedorDeElementos.agregarElemento(lanzaCohetes);
  }
}

void Map::sacarDelMapa(Posicion& posicion){
  this->contenedorDeElementos.sacarElementoDePosicion(posicion);
}

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

bool  idValido(std::vector<int>& idCargados, int& idPosible){
    bool es_valida = true;
    int i = 0;
    while (i < idCargados.size() && es_valida){
        if(idCargados[i] == idPosible){
            es_valida = false;
        }
    }
    return es_valida;
}
int Map::crearIdValido(){
    srand(time(NULL));
    int idPosible = 0;
    do{
    idPosible = rand() % 1000;
  }while(!idValido(this->idCargados, idPosible));
  this->idCargados.push_back(idPosible);
  return idPosible;

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

        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Comida(posicion,idValido));
    } else if (value == Type::sangre) {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Sangre(posicion,idValido));
    } else if (value == Type::kitsMedicos) {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new KitsMedicos(posicion, idValido));
    } else if (value == Type::balas) {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Balas(posicion, BALAS, idValido));
    } else if (value == Type::ametralladora) {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Ametralladora(posicion, idValido));
    } else if (value == Type::canionDeCadena) {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new CanionDeCadena(posicion, idValido));
    } else if (value == Type::lanzaCohetes) {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new LanzaCohetes(posicion, idValido));
    } else if (value == Type::cruz){
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Tesoro(idValido,Type::cruz, PUNTOS_CRUZ, posicion));
    } else if (value == Type::copa) {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Tesoro(idValido,Type::copa, PUNTOS_COPA, posicion));
    } else if (value == Type::cofre){
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Tesoro(idValido,Type::cofre, PUNTOS_COFRE, posicion));
    } else if (value == Type::corona){
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Tesoro(idValido,Type::corona, PUNTOS_CORONA, posicion));
    } else if (value == Type::llave) {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new Llave(posicion,idValido));
    } else {
        int idValido = this->crearIdValido();
        this->contenedorDeElementos.agregarElemento(new NoItem(posicion, idValido));
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
